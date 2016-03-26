#Buffer Overflows

A [buffer overflow](https://www.owasp.org/index.php/Buffer_overflow_attack) is one of the simplest types of binary exploits. It is usually the first thing that is taught to aspiring hackers, so it will be the first thing we go over in this guide. There are many many [examples](http://www.thegeekstuff.com/2013/06/buffer-overflow/), [tutorials](https://www.exploit-db.com/docs/28475.pdf), and [writeups](http://ehsandev.com/pico2014/binary_exploitation/overflow1.html) available online. My personal favorite is this
[interactive buffer overflow](https://picoctf.com/problem-static/binary/Overflow1/overflow1.html#1), which provides an excellent visualization of exactly what is happening during the exploit.

We have compiled a set of practice challenges in the *buffer overflow* directory. For each challenge, use your knowledge of assembly, gdb, and Python to create your exploit and understand *exactly what is happening*. Remember, getting a shell is good, but understanding *why* you got that shell is even more important. Use gdb to step though the program one instruction at a time and try to understand exactly what is happening at each step.



###  Making your life easier

 Now that you have a decent understanding of basic concepts, we can start making your life easer with some tools.
#### struct.pack()

If you are having problems with [endianness](http://www.geeksforgeeks.org/little-and-big-endian-mystery/), you can use `struct.pack()` to make your life easier.  We suggest reading though a few [examples](https://docs.python.org/2/library/struct.html#examples) and [tutorials](https://pymotw.com/2/struct/) to better understand this function and what it does. A basic example would be

```py
from struct import *

myHexString = struct.pack("<I",0xdeadbeef)

print myHexString
```



#### pwntools

[pwntools](https://github.com/Gallopsled/pwntools) is awesome. Once you start using it, you will wonder how you ever lived without it. Socket programming, packing hex values, and just about every other aspect of CTFs is made easier by this wonderful tool. For example, instead of using `struct.pack()`, you can do

```py
from pwn import *

myHexString = p32(0xdeadbeeef)

print myHexString
```

To find out more, read through [the documentation](https://pwntools.readthedocs.org/en/2.2/).

#### Python and GDB

While being able to pipe your exploit into a binary is good, sometimes your exploit won't work and you will have no idea why. To see what is happening, from the command line you can run

    python test.py > in
    gdb ./<binary>

Then, in gdb

    r < in

Now, you can step though the assembly and see what happens. If you are playing a [wargame](http://pwnable.kr/) and need to pass [command line arguments](http://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm), in gdb, run

    r $(python -c 'print "whatever you want" ')

### Emulating the CTF environment
In real life CTFs, challenges will be hosted on a remote server that you will have to connect to with a socket. So, to emulate this on your local machine
you should create a `run.sh` script and an `exploit.py` as we did in [the last section](https://github.com/kablaa/CTF-Workshop/blob/master/guide.md#2-basic-scripting) for each challenge.
