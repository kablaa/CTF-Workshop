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
  2) Dual boot your Current OS with Linux, or
  3) Get a [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine).
  </pre>          

We suggest getting a virtual machine. Learning your way around the Linux environment can be a daunting task if you are new to computers or are not familiar with using a terminal, so having a disposable system on which you can practice and experiment is incredibly advantageous.

### 1.1 Setting up your virtual machine

In theory, setting up an Ubuntu virtual machine should be relatively easy; however, you may encounter one of several bugs or errors due to no fault of your own. Because every situation is different, we will not be able to enumerate every possible challenge you may come across while setting up your VM. As with everything else in Computer Science, [Google](http://www.google.com) is your best friend. Make sure to read all errors carefully and to search for any error codes.

The first thing you need to do is [download](http://www.virtualbox.org) some vitalization software. The next thing you will need is a [.iso file](http://www.ubuntu.com/download/desktop). Once you have successfully acquired both of those things, you can follow one of several [tutorials](https://jtreminio.com/2012/04/setting-up-an-ubuntu-vm-step-by-step/) to get your VM up and running.

#### Virtualbox Guest Additions

If you successfully get your virtual machine up and running, you may notice that you can not maximize the screen. This is because you need to install the [virtualbox guest additions](http://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm). If you can successfully do this, you should a very nice desktop environment to work with.

### 1.2 Learning Linux Commands

[Learning the Linux command line](http://www.linuxcommand.org) is absolutely vital to cyber security of any kind. Pretty much every executable in a CTF will be run via the command line, and most tools available for CTFs are command line based. Plus, you can make the text green and look just like those super leet hackers you see in the movies all the time. If you haven't used a terminal before, we would highly recommend spending some time learning your way around the Linux environment. In particular, opening and [editing files](https://en.wikipedia.org/wiki/Vim_%28text_editor%29), running executables, and using [git](https://git-scm.com/) will be essential for the remainder of this guide.

## 2\. Learn Yo-Self Some Assembly

Learning Assembly is probably the most difficult and time consuming challenge for noobies. It can be incredibly intimidating to see hundreds of lines of low level system instructions. But take heart! The truth is, while reading and understanding Assembly can be very time consuming and tedious, it's not very complicated. There are really only a handful of instructions that you need to know off the top of your head. The real challenge is understanding and being able to visualize the stack. This is a topic that is disgracefully glossed over by most introductory programming classes and tutorials. However, with practice and patients, you will find that reading assembly can become almost second nature.

[Here](https://github.com/kablaa/CTF-Workshop/blob/master/x86Assembly.pdf) is small introduction to assembly and the stack. Before continuing with this guide, please study and do your best to understand each slide. Once you have read through the slides, go to [this](https://gcc.godbolt.org/) site and try decompiling some programs. Make sure to set the compiler type to `x86 clang 3.7.1`, put `-m32`in the compiler options box,  and set the syntax to `Intel` Start off with a simple `hello_world` program. Once you feel you understand what is happening in the assembly, try writing a program with some if-then statements and loops. While at first you may feel confused, keep experimenting.

Again, Google is your best friend. The best advise for learning assembly is to practice practice practice and don't give up! There is also a great [book](https://leaksource.files.wordpress.com/2014/08/hacking-the-art-of-exploitation.pdf) that introduces the basics of 32 bit assembly, static and dynamic analysis, as well as buffer overflows. Reading through this book is almost guaranteed to expedite your learning.

## 3\. Start Reversing Binaries

### 3.1 Static Analysis

#### Strings
`strings` is a standard tool for most linux systems that allows you to search for all strings within a particular file. This is very handy for finding bits and pieces of static data within a binary, as you do not have to search for it by hand in a hex editor. For options and how to use them, `man strings` will tell you everything you need to know (really, its an easy tool to use).

#### File
`file` is a tool that attempts to provide basic information regarding what type of file you provide it. This can be helpful for identifying how to approach a particular binary. An example can be seen below, where we run it against a basic executable:
```
redacted@ubuntu:~$ file a.out
a.out: ELF 64-bit LSB  executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=beb27b3da4fc2e516f2e0279f5c83b4e046fad5f, not stripped
```

#### Objdump
`objdump` is a critical tool for most things regarding executables. It allows you to convert the executable into it's assembly equivalent, allowing you to read the instructions it will be executing when it is running. The main command that will be used is: `objdump -d -M intel <input file name> > <output file>`.
The output file shold have a `.asm` extention. After you have decompiled the binary, you may open up the output file in your favorite text editor. Then, search for the `<main>`function.

### 3.2 Dynamic Analysis

Performing Dynamic Analysis involves examining and attempting to understand the inner workings of a binary while it is being run. This process usually involves using a [debugger](https://en.wikipedia.org/wiki/Debugger) to examine the states of registers, the stack, and the program flow at certain points during execution.

#### GDB

[GDB](https://www.gnu.org/software/gdb/) is the standard for debugging Linux executables. While learning GDB can be a daunting task for beginners, it is an incredibly powerful tool. In addition to this guide, which will be going over the most commonly used commands, there are several [tutorials](http://www.unknownroad.com/rtfm/gdbtut/) available for reference and practice. If it does not already come pre-installed on your distro, you can usually get it from an official repository. On Ubuntu, simply run

      sudo apt-get install gdb


#### GDB-PEDA

PEDA stands for Python Exploit Development Assistance. This tool will make your life exceptionally easier during the debugging process. You can clone it from the [github repository](https://github.com/longld/peda) and follow the installation instructions on the README. For more information on PEDA, check out [this](http://security.cs.pub.ro/hexcellents/wiki/kb/toolset/peda) tutorial. Note that PEDA requires Python version 2.x, so if you are currently using Python 3.x, you will have to switch your version.

### 3.3 Practice

Reversing binaries in inherently difficult, and learning to do it efficiently takes a great deal of time and practice. We have compiled a set of binaries that we suggest you start reversing. You can get them here:

[http://github.com/kablaa/CTF-Workshop](http://github.com/kablaa/CTF-Workshop)

After you have cloned the repository, read the README file, follow the setup instructions, and navigate to the _reversing_ directory. Then, read TODO.txt and get to work! We also suggest spending as much time as possible on sites like [crackmes.de](http://www.crackmes.de) as well as writing and reversing your own binaries. There are even several [books](http://www.ece.ualberta.ca/~marcin/aikonsoft/reverse.pdf) and [tutorials](http://manoharvanga.com/hackme/) written and on the subject of reversing Linux binaries.

## 4\. Python Scripting

### 4.1 Sockets

#### Sockets in Python

#### Testing with SoCat and NetCat

### 4.2 Python and GDB

### 4.3 Hexadecimal Values

#### struct.pack()

#### pwntools

# Get Hacking

## 1\. Buffer Overflows

[bof writeup](http://ehsandev.com/pico2014/binary_exploitation/overflow1.html)

[Interactive buffer overflow](https://picoctf.com/problem-static/binary/Overflow1/overflow1.html#1)

## 2\. ROP ROP ROP

## 3\. Shellcode
