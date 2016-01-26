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

When it comes to getting Linux, you basically you have three options:
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

Learning [Assembly](http://www.swansontec.com/sprogram.html) is probably the most difficult and time consuming challenge for noobies. It can be incredibly intimidating to see hundreds of lines of low level system instructions. But take heart! The truth is, while reading and understanding Assembly can be very time consuming and tedious, it's not very complicated. There are really only a handful of instructions that you need to know off the top of your head. The real challenge is understanding and being able to visualize the stack. This is a topic that is disgracefully glossed over by most introductory programming classes and tutorials. However, with practice and patients, you will find that reading assembly can become almost second nature.

[Here](https://github.com/kablaa/CTF-Workshop/blob/master/x86Assembly.pdf) is small introduction to assembly and the stack. Before continuing with this guide, please study and do your best to understand each slide. Once you have read through the slides, go to [this](https://gcc.godbolt.org/) site and try decompiling some programs. Make sure to set the compiler type to `x86 clang 3.7.1`, put `-m32`in the compiler options box,  and set the syntax to `Intel` Start off with a simple `hello_world` program. Once you feel you understand what is happening in the assembly, try writing a program with some if-then statements and loops. While at first you may feel confused, keep experimenting.

Again, Google is your best friend. The best advise for learning assembly is to practice practice practice and don't give up! There is also a great [book](https://leaksource.files.wordpress.com/2014/08/hacking-the-art-of-exploitation.pdf) that introduces the basics of 32 bit assembly, static and dynamic analysis, as well as buffer overflows. Reading through this book is almost guaranteed to expedite your learning.



## 3. Python Scripting

 Knowing at least one scripting language will make your life exceptionally easier no matter which field of Computer Science you chose to pursue. Playing CTFs without knowing one is almost impossible. Before we get into Python, let's get this out of the way...

### I Don't Care If You Think Ruby is Better
 We chose to go over python because we fucking felt like it. If you have a problem with that, you can open up EMACS, write your own guide in LaTeX, and talk about how much you love Ruby there. Ok, now that that's over with let talk about sockets.  

### 3.1 Sockets
[more information on sockets](http://www.tutorialspoint.com/unix_sockets/what_is_socket.htm)

[netcat](https://www.digitalocean.com/community/tutorials/how-to-use-netcat-to-establish-and-test-tcp-and-udp-connections-on-a-vps)

#### Sockets in Python

[tutorial](http://www.tutorialspoint.com/python/python_networking.htm)

### 3.2 Python and GDB

#### Testing your exploit in gdb
    python test.py > in

  Then, in gdb

    r < in



# Start Hacking Shit

We have provided you with a set of practice challenges [here](https://github.com/kablaa/CTF-Workshop). These challenges are meant to be solved in the Linux environment, so boot up that virtual machine we talked about in [section 1](https://github.com/kablaa/CTF-Workshop/blob/master/guide.md/#getting-started). Make sure you have `git` installed. On Ubuntu you can get it with

    sudo apt-get install git

Then, follow the [setup instructions](https://github.com/kablaa/CTF-Workshop/blob/master/README.md#setup).  Once you are sure that you are comfortable with all of the concepts in the previous sections, you can move on to the challenges.


## 1. Reverse Engineering

### 1.1 Static Analysis

#### Objdump
`objdump` is a critical tool for most things regarding executables. It allows you to convert the executable into it's assembly equivalent, allowing you to read the instructions it will be executing when it is running. The main command that will be used is: `objdump -d -M intel <input file name> > <output file>`.
The output file shold have a `.asm` extention. After you have decompiled the binary, you may open up the output file in your favorite text editor. Then, search for the `<main>`function.


#### Strings
`strings` is a standard tool for most Linux systems that allows you to search for all strings within a particular file. This is very handy for finding bits and pieces of static data within a binary, as you do not have to search for it by hand in a hex editor. For options and how to use them, `man strings` will tell you everything you need to know (really, its an easy tool to use).

#### File
`file` is a tool that attempts to provide basic information regarding what type of file you provide it. This can be helpful for identifying how to approach a particular binary. An example can be seen below, where we run it against a basic executable:
```
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

Reversing binaries in inherently difficult, and learning to do it efficiently takes a great deal of time and practice. We have compiled a set of binaries that we suggest you start reversing. You can find them by navigating to the *reversing* directory. Then, read TODO.txt and get to work! We also suggest spending as much time as possible on sites like [crackmes.de](http://www.crackmes.de) as well as writing and reversing your own binaries. There are even several [books](http://www.ece.ualberta.ca/~marcin/aikonsoft/reverse.pdf) and [tutorials](http://manoharvanga.com/hackme/) written and on the subject of reversing Linux binaries.

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


### 3.2 What is a buffer overflow?

[Interactive buffer overflow](https://picoctf.com/problem-static/binary/Overflow1/overflow1.html#1)

### 3.3 Endianness

### What is Endianness?

You can find an example demonstrating Endianness in the _examples_ directory.

### Why is Endianness Important?

### 3.4 Hexadecimal Values in Python

#### struct.pack()

#### pwntools

### 3.5 Bringing it all together

Read this
[writeup](http://ehsandev.com/pico2014/binary_exploitation/overflow1.html), once you feel you understand all of the concepts, you can start working on the practice challenges. Navigate to the `buffer_overflow` directory, read the TODO.txt and work your way through the challenges.

#### Emulating the CTF environment
In real life CTFs, challenges will be hosted on a remote server that you will have to connect to with a socket. So, to emulate this on your local machine
you should create a `run.sh` script and an `exploit.py` as we did in [the last section](https://github.com/kablaa/CTF-Workshop/blob/master/guide.md#1-basic-scripting) for each challenge. You can test your exploit as we did in [section 3](https://github.com/kablaa/CTF-Workshop/blob/master/guide.md#32-python-and-gdb). Once you understand how to solve the challenge, write your exploit in `exploit.py` and use the socket to send your payload.
