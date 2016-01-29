# get_flag Writeup

## Recon
The first step in approaching this challenge is to get the assembly for the program in question. In this case, the get_flag executable. To do this, we do: `objdump -d -M intel get_flag > get_flag.asm`. From this, we can see that we have the functions `winner`, `pass2`, and `pass1`. Therefore, these are the functions that we are going to place breakpoints on in gdb.

Doing some further recon by walking the code execution path from the `main` function will allow us to see how it calls the `pass1` function. If we then look at the `pass1` function, we can see that `pass2` is called within it. Therefore, we can determine that the `winner` function is never called, and we dont have to worry about it.

## Vulnerability analysis
The first thing to do when looking at how to exploit this particular application is to find the system call. In this case, it is within the `pass2` function:
```asm
80484b9:       e8 92 fe ff ff          call   8048350 <system@plt>
```
Therefore, we need to find the route to get `pass2` to execute.

## Exploitation
To actually exploit this application and get `pass2` to execute, we must start walking the instructions leading up to the `pass2` call.

Beginning in main, we can see that there is a `read` call:
```asm
8048520:       e8 0b fe ff ff          call   8048330 <read@plt>
```
This means that we are likely reading in from a file object. In this case, we can begin to look at the arguments for this function to help determine what we are reading from:
```asm
8048518:       6a 40                   push   0x40
804851a:       8d 45 b8                lea    eax,[ebp-0x48]
804851d:       50                      push   eax
804851e:       6a 00                   push   0x0
```
Based on this, we can assume that it is reading in from standard input (denoted by the file object `0`), and reading the input into a buffer at `[ebp-0x48]`.

Moving further down the execution path, we can see that we have our first call to `pass1`:
```asm
8048525:       83 c4 10                add    esp,0x10
8048528:       83 ec 0c                sub    esp,0xc
804852b:       8d 45 b8                lea    eax,[ebp-0x48]
804852e:       50                      push   eax
804852f:       e8 8f ff ff ff          call   80484c3 <pass1>
```
From this we can see that it passes `[ebp-0x48]` to the `pass1` function. Therefore, we need to move into the `pass1` function to continue tracing the execution path.

Within `pass1`, skipping the prologue of the function, we can see that there are several interesting things. First of all, we can see that there are references to `pass2` as well as `strncmp`. First up is `strncmp`. Googling for the docs for `strncmp` we can see that it takes 3 arguments. 2 strings and a length of the strings to compare. Knowing this, we can begin to make sense of the arguments to look for above the call:
```asm
80484cc:       6a 0a                   push   0xa
80484ce:       68 f0 85 04 08          push   0x80485f0
80484d3:       ff 75 08                push   DWORD PTR [ebp+0x8]
80484d6:       e8 a5 fe ff ff          call   8048380 <strncmp@plt>
```
In this case, we have 3 arguments being pushed to the stack. `0xa`, `0x80485f0`, and `[ebp+0x8]`. In this case, we can assume that `0xa` is the length of the string we are comparing, and `[ebp+0x8]` is our supplied string. Therefore, we need to figure out the other argument `0x80485f0`, which appears to be something that was compiled into the program. Because of this, we need to find out what it is within gdb. So:
```
gdb-peda$ x/s 0x80485f0
0x80485f0:	"iamahacker"
```
So now that we know that this is, we can also count and see that `"iamahacker"` has a string length of ten. This means when the `strncmp` is called, it is comparing the first 10 characters of our string to `"iamahacker"` to make sure it is true. To test this, we can enter `iamahacker` to the input in gdb and find out that the `test` goes through without jumping (`jne` is not executed). This means that we have code execution to the `pass2` function. However, note what happens when we simply put `iamahacker` when we run it in the console:
```sh
# ./get_flag
iamahacker
sh: 2: ���^�: not found
```
We officially have a call to the `system` function. However, we aren't suplying it with anything. If we recall, only the first 10 characters of the string are compared. This means that we can add extra things to our input. If we also look at the `pass2` function, we can see that the first 10 characters are removed from the string it is passed:
```asm
80484a9:       8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
80484ac:       89 45 f4                mov    DWORD PTR [ebp-0xc],eax
80484af:       83 45 f4 0a             add    DWORD PTR [ebp-0xc],0xa
```
Followed by the system call:
```asm
80484b6:       ff 75 f4                push   DWORD PTR [ebp-0xc]
80484b9:       e8 92 fe ff ff          call   8048350 <system@plt>
```
Therefore, if we were to enter something such as: `iamahackercat flag` we are able to actually get the flag, since the first 10 characters of the string pass the comparison and are removed, leaving `cat flag`:
```sh
# ./get_flag
iamahackercat flag
you got your first flag!! :)
```
Congratulations, you owned your first challenge!
