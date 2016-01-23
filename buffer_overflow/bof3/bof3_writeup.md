# Bof3 Writeup

## recon
The first step to breaking this binary is to get the ASM output of the binary. This can be done through: `objdump -d -M intel bof3 > bof3.asm`. After is done, you can begin determining which functions are breakable in GDB.
