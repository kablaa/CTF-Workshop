[![hackucf logo](https://github.com/kablaa/CTF-Workshop/blob/master/Exploitation/HackUCF.png)](http://www.hackucf.org)

## Read the full introduction at [Hack My World](https://hackmy.world/projects/tutorial.php)

**Requirements**:
    Linux, gcc, socat, and gcc-multilib to run and create 32 bit executables.

To get gcc-multilib on Ubuntu, you may run:

    sudo apt-get install gcc-multilib

Otherwise you will have to Google for the installation instructions specific to your distro.

##Setup:

    git clone https://github.com/kablaa/CTF-Workshop.git ~/Workshops





# Welcome!

This is a guide that was written with intention of taking you through the process of learning how to play [Capture the Flag](https://en.wikipedia.org/wiki/Capture_the_flag#Computer_security) (CTF). This is by no means intended to be a comprehensive tutorial. Our intention here is simply to provide you with the tools you need to become familiar with the game and get started on your quest to become a leet hacker.

### Prerequisites

This guide assumes that you have a working knowledge of the [C programming language](https://www.scaler.com/topics/c/). We do not expect you to be an enterprise level developer; however, we will assume a working knowledge of functions, variables, pointers, etc. A basic understanding of [Python](http://www.python.org) is also highly recommended. While we will be going over the aspects of Python scripting that are most important to CTFs, reading through a few [tutorials](http://www.tutorialspoint.com/python) will be extremely helpful. If you have never programmed before, or do not feel you are comfortable with these concepts, the great interwebs is full of comprehensive [tutorials and guides](http://www.tutorialspoint.com/computer_programming/). A computer capable of handling a Linux virtual machine is also required.


### What is Capture the Flag?

CTFs are competitions in which players are given challenges related to several fields of cyber security. [Challenges](http://www.github.com/ctfs) usually fall into one of the following categories:

*   [Reverse Engineering](https://en.wikipedia.org/wiki/Reverse_engineering)
*   [Binary](https://en.wikipedia.org/wiki/Executable) Exploitation
*   Web
*   Cryptography
*   Forensics

Normally, players will specialize in one of these categories. Although it is possible to have a basic knowledge of all of them, we suggest you begin by focusing on the one that interests you most. This guide will be focusing On Binary Exploitation.

# Getting Started

## Get yo-self some Linux

Pretty much any CTF worth it's salt is going to require a working knowledge of [Linux](https://en.wikipedia.org/wiki/Linux). Binary exploitation challenges in particular are almost exclusively limited to the Linux environment. What is Linux you ask? Well, it's an operating System. However, unlike Windows or the Apple OS, Linux is [open source](https://en.wikipedia.org/wiki/Open_source), so it's completely free! Also, because Linux is open source, developers have the opportunity to create various styles or flavors of Linux. These styles of Linux are referred to as Distributions. We recommend getting [Ubuntu](http://www.ubuntu.com), as it is the most popular and beginner friendly distro.

When it comes to getting Linux, you basically you have four options:
  <pre>
  1) Wipe your current OS and replace it with Linux,
  2) Dual boot your Current OS with Linux,
  3) Boot Linux off of a USB drive, or
  4) Get a [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine).
  </pre>          

We suggest getting a virtual machine. Learning your way around the Linux environment can be a daunting task if you are new to computers or are not familiar with using a terminal, so having a disposable system on which you can practice and experiment is incredibly advantageous.

### Setting up your virtual machine

In theory, setting up an Ubuntu virtual machine should be relatively easy; however, you may encounter one of several bugs or errors due to no fault of your own. Because every situation is different, we will not be able to enumerate every possible challenge you may come across while setting up your VM. As with everything else in Computer Science, [Google](http://www.google.com) is your best friend. Make sure to read all errors carefully and to search for any error codes.

The first thing you need to do is [download](http://www.virtualbox.org) some virtualization software. The next thing you will need is a [.iso file](http://www.ubuntu.com/download/desktop). Once you have successfully acquired both of those things, you can follow one of several [tutorials](https://jtreminio.com/2012/04/setting-up-an-ubuntu-vm-step-by-step/) to get your VM up and running.

#### Enabling Virtualization
Due to the infinite wisdom of many hardware manufacturers these days, you may need to enable virtualization on your motherboard.
[here](http://www.howtogeek.com/213795/how-to-enable-intel-vt-x-in-your-computers-bios-or-uefi-firmware/) is a tutorial on how to do that.

#### Virtualbox Guest Additions

If you successfully get your virtual machine up and running, you may notice that you can not maximize the screen. This is because you need to install the [virtualbox guest additions](http://askubuntu.com/questions/22743/how-do-i-install-guest-additions-in-a-virtualbox-vm). If you can successfully do this, you should a very nice desktop environment to work with.

### Learning Linux Commands

[Learning the Linux command line](http://www.linuxcommand.org) is absolutely vital to cyber security of any kind. Pretty much every executable in a CTF will be run via the command line, and most tools available for CTFs are command line based. Plus, you can make the text green and look just like those super leet hackers you see in the movies all the time. If you haven't used a terminal before, we would highly recommend spending some time learning your way around the Linux environment. In particular, opening and [editing files](https://en.wikipedia.org/wiki/Vim_%28text_editor%29), running executables, and using [git](https://git-scm.com/) will be essential for the remainder of this guide.


###Level 1: **reversing**

###Level 2: **scripting**

###Level 3: **Exploitation**

##More Resources: 

[Smash the Stack](https://avicoder.me/2016/02/01/smashsatck-revived/)

[Owen Redwood Lectures](http://www.cs.fsu.edu/~redwood/OffensiveComputerSecurity/lectures.html)
    

[Really good Youtube series](https://www.youtube.com/watch?v=iyAyN3GFM7A&list=PLhixgUqwRTjxglIswKp9mpkfPNfHkzyeN)

[shamelss self promotion](https://www.youtube.com/watch?v=75gBFiFtAb8)
