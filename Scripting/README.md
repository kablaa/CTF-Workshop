#  Python Scripting

 Knowing at least one scripting language will make your life exceptionally easier no matter which field of Computer Science you choose to pursue. Playing CTFs without knowing one is almost impossible. Before we get into Python, let's get this out of the way...

#### I Don't Care If You Think Python Sucks

 We chose to go over Python because we felt like it. If you have a problem with that, you can open up EMACS, write your own CTF guide in LaTeX, and talk about how much you love Ruby there. Ok, now that that's over with lets talk about sockets.  

### 1 Sockets

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

### Sockets in Python

Python will allow you to connect to a socket on a port and send whatever data you want, as well as receive data through the socket. Before continuing with this guide, read though a few [tutorials](http://www.tutorialspoint.com/python/python_networking.htm) on socket programming in Python. Write some example programs and test out the various types of things you can do with sockets. Remember, you only need a very high level of understanding of sockets in order to play CTFs. So if you find yourself reading about Ethernet II on Wikipedia, you have probably gone too deep.


###   Hexadecimal Values in Python

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



##  Practice

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
