# Bof3 Writeup

## recon
The first step to breaking this binary is to get the ASM output of the binary. This can be done through: `objdump -d -M intel bof3 > bof3.asm`. After is done, you can begin determining which functions are breakable in GDB.

As we scroll through the asm file in an editor of your choice, we will see that there are `win, lose, and main` functions. These are the functions in which we will need to set breakpoints so that we can begin to walk the code execution paths.

## Vulnerability Analysis
Looking at the individual functions, we can begin to see the general idea for the code execution path of the program.

Within the main function, we can see references to the lose function:
```
   0x804851c <main+41>:	add    esp,0x10
   0x804851f <main+44>:	mov    eax,DWORD PTR [ebp-0xc]
=> 0x8048522 <main+47>:	call   eax
```
Based on this, we can tell that we need to overwrite the code execution path so that we do not hit the lose function. In this case, it requires us overwritting the value of `EAX` before
