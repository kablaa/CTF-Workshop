#  Learn Yo-Self Some Assembly

Learning [Assembly](http://www.swansontec.com/sprogram.html) is probably the most difficult and time consuming challenge for noobies. It can be incredibly intimidating to see hundreds of lines of low level system instructions. But take heart! The truth is, while reading and understanding Assembly can be very time consuming and tedious, it's not very complicated. There are really only a handful of instructions that you need to know off the top of your head. The real challenge is understanding and being able to visualize the stack. This is a topic that is disgracefully glossed over by most introductory programming classes and tutorials. However, with practice and patience, you will find that reading assembly can become almost second nature.

[Here](https://github.com/kablaa/CTF-Workshop/blob/master/Reversing/Other/ReadingAssembly/x86Assembly.pdf) is small introduction to assembly and the stack. Before continuing with this guide, please study and do your best to understand each slide. Once you have read through the slides, go to [this](https://gcc.godbolt.org/) site and try decompiling some programs. Make sure to set the compiler type to `x86 clang 3.7.1`, put `-m32`in the compiler options box,  and set the syntax to `Intel` Start off with a simple `hello_world` program. Once you feel you understand what is happening in the assembly, try writing a program with some if-then statements and loops. While at first you may feel confused, keep experimenting.

Again, Google is your best friend. The best advise for learning

### Getting Some Tools

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


###  Dynamic Analysis

Performing Dynamic Analysis involves examining and attempting to understand the inner workings of a binary while it is being run. This process usually involves using a [debugger](https://en.wikipedia.org/wiki/Debugger) to examine the states of registers, the stack, and the program flow at certain points during execution.

#### GDB

[GDB](https://www.gnu.org/software/gdb/) is the standard for debugging Linux executables. While learning GDB can be a daunting task for beginners, it is an incredibly powerful tool. There are several [tutorials](http://www.unknownroad.com/rtfm/gdbtut/) available for reference and practice. If it does not already come pre-installed on your distro, you can usually get it from an official repository. On Ubuntu, simply run

      sudo apt-get install gdb


#### GDB-PEDA

PEDA stands for Python Exploit Development Assistance. This tool will make your life exceptionally easier during the debugging process. You can clone it from the [github repository](https://github.com/longld/peda) and follow the installation instructions on the README. For more information on PEDA, check out [this](http://security.cs.pub.ro/hexcellents/wiki/kb/toolset/peda) tutorial. Note that PEDA requires Python version 2.x, so if you are currently using Python 3.x, you will have to switch your version.

###  Practice

Reversing binaries is inherently difficult, and learning to do it efficiently takes a great deal of time and practice. We have compiled a set of binaries that we suggest you start reversing. You can find them by navigating to the *reversing* directory. Then, read TODO.txt and get to work! We also suggest spending as much time as possible on sites like [crackmes.de](http://www.crackmes.de) and [reversing.kr](http://reversing.kr/) as well as writing and reversing your own binaries. There are even several [books](http://www.ece.ualberta.ca/~marcin/aikonsoft/reverse.pdf) and [tutorials](http://manoharvanga.com/hackme/) written and on the subject of reversing Linux binaries.
