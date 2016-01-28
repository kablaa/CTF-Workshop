# Welcome!

This is a guide that was written with intention of taking you through the process of learning how to play [Capture the Flag](https://en.wikipedia.org/wiki/Capture_the_flag#Computer_security) (CTF). This is by no means intended to be a comprehensive tutorial. Our intention here is simply to provide you with the tools you need to become familiar with the game and get started on your quest to become a leet hacker.

### Prerequisites

This guide assumes that you have a working knowledge of the C programming language. We do not expect you to be an enterprise level developer; however, we will assume a working knowledge of functions, variables, pointers, etc. A basic understanding of [Python](http://www.python.org) is also highly recommended. While we will be going over the aspects of Python scripting that are most important to CTFs, reading through a few [tutorials](http://www.tutorialspoint.com/python) will be extremely helpful. If you have never programmed before, or do not feel you are comfortable with these concepts, the great interwebs is full of comprehensive [tutorials and guides](http://www.tutorialspoint.com/computer_programming/). A computer capable of handling a Linux virtual machine is also required.


### What is Capture the Flag?

CTFs are competitions in which players are given challenges related to several fields of cyber security. [Challenges](http://www.github.com/ctfs) usually fall into one of the following categories:

*   [Reverse Engineering](https://en.wikipedia.org/wiki/Reverse_engineering)
*   [Binary](https://en.wikipedia.org/wiki/Executable) Exploitation
*   Web
*   Cryptography
*   Forensics

Normally, players will specialize in one of these categories. Although it is possible to have a basic knowledge of all of them, we suggest you begin by focusing on the one that interests you most. This guide will be focusing On Binary Exploitation.

# Getting Started

## 1\. Get yo-self some Linux

Pretty much any CTF worth it's salt is going to require a working knowledge of [Linux](https://en.wikipedia.org/wiki/Linux). Binary exploitation challenges in particular are almost exclusively limited to the Linux environment. What is Linux you ask? Well, it's an operating System. However, unlike Windows or the Apple OS, Linux is [open source](https://en.wikipedia.org/wiki/Open_source), so it's completely free! Also, because Linux is open source, developers have the opportunity to create various styles or flavors of Linux. These styles of Linux are referred to as Distributions. We recommend getting [Ubuntu](http://www.ubuntu.com), as it is the most popular and beginner friendly distro.

When it comes to getting Linux, you basically you have four options:
  <pre>
  1) Wipe your current OS and replace it with Linux,
  2) Dual boot your Current OS with Linux,
  3) Boot Linux off of a USB drive, or
  4) Get a [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine).
  </pre>          

We suggest getting a virtual machine. Learning your way around the Linux environment can be a daunting task if you are new to computers or are not familiar with using a terminal, so having a disposable system on which you can practice and experiment is incredibly advantageous.

### 1.1 Setting up your virtual machine

In theory, setting up an Ubuntu virtual machine should be relatively easy; however, you may encounter one of several bugs or errors due to no fault of your own. Because every situation is different, we will not be able to enumerate every possible challenge you may come across while setting up your VM. As with everything else in Computer Science, [Google](http://www.google.com) is your best friend. Make sure to read all errors carefully and to search for any error codes.

The first thing you need to do is [download](http://www.virtualbox.org) some virtualization software. The next thing you will need is a [.iso file](http://www.ubuntu.com/download/desktop). Once you have successfully acquired both of those things, you can follow one of several [tutorials](https://jtreminio.com/2012/04/setting-up-an-ubuntu-vm-step-by-step/) to get your VM up and running.

#### Enabling Virtualization
Due to the infinite wisdom of many hardware manufacturers these days, you may need to enable virtualization on your motherboard.
[here](http://www.howtogeek.com/213795/how-to-enable-intel-vt-x-in-your-computers-bios-or-uefi-firmware/) is a tutorial on how to do that.

#### Virtualbox Guest Additions

If you successfully get your virtual machine up and running, you may notice that you can not maximize the screen. This is because you need to install the [virtualbox guest additions](http://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm). If you can successfully do this, you should a very nice desktop environment to work with.

### 1.2 Learning Linux Commands

[Learning the Linux command line](http://www.linuxcommand.org) is absolutely vital to cyber security of any kind. Pretty much every executable in a CTF will be run via the command line, and most tools available for CTFs are command line based. Plus, you can make the text green and look just like those super leet hackers you see in the movies all the time. If you haven't used a terminal before, we would highly recommend spending some time learning your way around the Linux environment. In particular, opening and [editing files](https://en.wikipedia.org/wiki/Vim_%28text_editor%29), running executables, and using [git](https://git-scm.com/) will be essential for the remainder of this guide.

## 2\. Learn Yo-Self Some Assembly

Learning [Assembly](http://www.swansontec.com/sprogram.html) is probably the most difficult and time consuming challenge for noobies. It can be incredibly intimidating to see hundreds of lines of low level system instructions. But take heart! The truth is, while reading and understanding Assembly can be very time consuming and tedious, it's not very complicated. There are really only a handful of instructions that you need to know off the top of your head. The real challenge is understanding and being able to visualize the stack. This is a topic that is disgracefully glossed over by most introductory programming classes and tutorials. However, with practice and patience, you will find that reading assembly can become almost second nature.

[Here](https://github.com/kablaa/CTF-Workshop/blob/master/x86Assembly.pdf) is small introduction to assembly and the stack. Before continuing with this guide, please study and do your best to understand each slide. Once you have read through the slides, go to [this](https://gcc.godbolt.org/) site and try decompiling some programs. Make sure to set the compiler type to `x86 clang 3.7.1`, put `-m32`in the compiler options box,  and set the syntax to `Intel` Start off with a simple `hello_world` program. Once you feel you understand what is happening in the assembly, try writing a program with some if-then statements and loops. While at first you may feel confused, keep experimenting.

Again, Google is your best friend. The best advise for learning assembly is to practice practice practice and don't give up! There is also a great [book](https://leaksource.files.wordpress.com/2014/08/hacking-the-art-of-exploitation.pdf) that introduces the basics of 32 bit assembly, static and dynamic analysis, as well as buffer overflows. Reading through this book is almost guaranteed to expedite your learning.



## 3. Python Scripting

 Knowing at least one scripting language will make your life exceptionally easier no matter which field of Computer Science you choose to pursue. Playing CTFs without knowing one is almost impossible. Before we get into Python, let's get this out of the way...

#### I Don't Care If You Think Python Sucks

 We chose to go over Python because we felt like it. If you have a problem with that, you can open up EMACS, write your own CTF guide in LaTeX, and talk about how much you love Ruby there. Ok, now that that's over with lets talk about sockets.  

### 3.1 Sockets

Most CTFs are going to be hosted on a remote server. For binary challenges, the flag will typically be in the same directory as the binary. You will have to find a way to exploit the binary and get a [shell](https://en.wikipedia.org/wiki/Unix_shell). Once you have the shell, you will usually run

    cat flag

which will print out the contents of the flag. So how do we interact with the binary if it's on another server? The answer is [sockets](https://en.wikipedia.org/wiki/Network_socket). A socket is essentially a network connection between your computer and another computer. Because multiple processes will often require access to a socket at the same time, we use [ports](https://simple.wikipedia.org/wiki/Network_port) so that we can connect to whichever specific process we want. There are several ports that are reserved for specific processes such as [SSH](https://en.wikipedia.org/wiki/Secure_Shell) (port 22), [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol) (port 25), and [HTTP](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) (port 80). You can go [here](http://www.tutorialspoint.com/unix_sockets/what_is_socket.htm) for more information on networking ports.

As far as CTFs go, we have what are referred to as _general purose_ ports. These are just ports that are not being used by any other service. Each challenge will be associated with a specific port. You will typically see something like

```
Challenge:

someCTF.coolhackerurl.we p-6666
```
So what you will have to do is connect to `someCTF.coolhackerurl.we` on `port 6666`. Then, instead of the output of the binary being written to [stdout](https://en.wikipedia.org/wiki/Standard_streams), it will be sent though the socket to your computer. Likewise, you will need to send your exploit through the socket.

So how do we connect to sockets? One way is to use [Netcat](https://www.digitalocean.com/community/tutorials/how-to-use-netcat-to-establish-and-test-tcp-and-udp-connections-on-a-vps). Netcat is the simplest way to connect to a socket. Just run

    nc someCTF.coolhackerurl.we 6666

Now, it will be just like you are running the executable on your home machine. You can send input and get output just like you normally would. However, what if you want to send something that can't be typed on a keyboard, like a hexadecimal value?

#### Sockets in Python

Python will allow you to connect to a socket on a port and send whatever data you want, as well as receive data through the socket. Before continuing with this guide, read though a few [tutorials](http://www.tutorialspoint.com/python/python_networking.htm) on socket programming in Python. Write some example programs and test out the various types of things you can do with sockets. Remember, you only need a very high level of understanding of sockets in order to play CTFs. So if you find yourself reading about Ethernet II on Wikipedia, you have probably gone too deep.


###  3.2 Hexadecimal Values in Python

For most binary challenges, you will need to input [hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal) values for a variety of reasons. To do this with python you must create string of hex values and send that string to your executable. For example, in your `exploit.py`, you can write

```py
myHexString = "\xde\xad\xbe\xef"

print myHexString
```

and then from the command line,

```sh
python exploit.py | ./<binary>
```

This will [pipe](http://ryanstutorials.net/linuxtutorial/piping.php) the output of your `exploit.py` script into your binary.

# Start Hacking Shit

We have provided you with a set of practice challenges [here](https://github.com/kablaa/CTF-Workshop). These challenges are meant to be solved in the Linux environment, so boot up that virtual machine we talked about in [section 1](https://github.com/kablaa/CTF-Workshop/blob/master/guide.md/#getting-started). Make sure you have `git` installed. On Ubuntu you can get it with

    sudo apt-get install git

Then, follow the [setup instructions](https://github.com/kablaa/CTF-Workshop/blob/master/README.md#setup).  Once you are sure that you are comfortable with all of the concepts in the previous sections, you can move on to the challenges.


## 1. Reverse Engineering

### 1.1 Static Analysis

#### Objdump
`objdump` is a critical tool for most things regarding executables. It allows you to convert the executable into it's assembly equivalent, allowing you to read the instructions it will be executing when it is running. The main command that will be used is:

`objdump -d -M intel <input file name> > dump.asm`.


After you have decompiled the binary, you may open up `dump.asm` in your favorite text editor. Then, search for the `<main>`function.


#### Strings
`strings` is a standard tool for most Linux systems that allows you to search for all strings within a particular file. This is very handy for finding bits and pieces of static data within a binary, as you do not have to search for it by hand in a hex editor. For options and how to use them, `man strings` will tell you everything you need to know (really, its an easy tool to use).

#### File
`file` is a tool that attempts to provide basic information regarding what type of file you provide it. This can be helpful for identifying how to approach a particular binary. An example can be seen below, where we run it against a basic executable:
```sh
redacted@ubuntu:~$ file a.out
a.out: ELF 64-bit LSB  executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=beb27b3da4fc2e516f2e0279f5c83b4e046fad5f, not stripped
```


### 1.2 Dynamic Analysis

Performing Dynamic Analysis involves examining and attempting to understand the inner workings of a binary while it is being run. This process usually involves using a [debugger](https://en.wikipedia.org/wiki/Debugger) to examine the states of registers, the stack, and the program flow at certain points during execution.

#### GDB

[GDB](https://www.gnu.org/software/gdb/) is the standard for debugging Linux executables. While learning GDB can be a daunting task for beginners, it is an incredibly powerful tool. There are several [tutorials](http://www.unknownroad.com/rtfm/gdbtut/) available for reference and practice. If it does not already come pre-installed on your distro, you can usually get it from an official repository. On Ubuntu, simply run

      sudo apt-get install gdb


#### GDB-PEDA

PEDA stands for Python Exploit Development Assistance. This tool will make your life exceptionally easier during the debugging process. You can clone it from the [github repository](https://github.com/longld/peda) and follow the installation instructions on the README. For more information on PEDA, check out [this](http://security.cs.pub.ro/hexcellents/wiki/kb/toolset/peda) tutorial. Note that PEDA requires Python version 2.x, so if you are currently using Python 3.x, you will have to switch your version.

### 1.3 Practice

Reversing binaries is inherently difficult, and learning to do it efficiently takes a great deal of time and practice. We have compiled a set of binaries that we suggest you start reversing. You can find them by navigating to the *reversing* directory. Then, read TODO.txt and get to work! We also suggest spending as much time as possible on sites like [crackmes.de](http://www.crackmes.de) and [reversing.kr](http://reversing.kr/) as well as writing and reversing your own binaries. There are even several [books](http://www.ece.ualberta.ca/~marcin/aikonsoft/reverse.pdf) and [tutorials](http://manoharvanga.com/hackme/) written and on the subject of reversing Linux binaries.

## 2. Basic Scripting

 Your next task is to practice your scripting skills. Navigate to the *scripting* directory. For this set of challenges, you will be using `socat` to create a network socket, listen on `port 1234` and run the executable. To do this, first make sure you have socat installed. On Ubuntu:

      sudo apt-get install socat


Then, in the directory associated with the challenge you are working on, run the command

    echo "socat -v tcp-l:1234,fork exec:'./<name_of_challenge>' " > run.sh

where `<name_of_challenge>` is the name of the binary you are currently working on. Then run

     chmod +x run.sh
    ./run.sh

You will notice that nothing happens. That is because your script is listening on port 1234. Now, you can minimize that terminal and open up a new one. From that terminal, navigate to the challenge directory and create an `exploit.py` with the lines

    HOST = 'localhost'
    PORT = 1234

  Your python script should open a socket connection to `HOST` on `PORT`. Each challenge will require you to send and receive data to and from the socket. From here on out, you will perform your exploits by sending and receiving data with a python script.

  You can find an example of an echo service, a python script that will communicate with it, and a run.sh file in the _examples_ directory.



## 3. Buffer Overflows

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
