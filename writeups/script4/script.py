from pwn import *

conn = remote('localhost',1234)

for i in range(0,10):
    data = conn.recvuntil("\n")
    print "recieved : " + data
    data = data.split("me ")[1]
    data = int(data,16)
    data = str(data)
    print "seding " + data
    conn.sendline(data);

print conn.recvline()
