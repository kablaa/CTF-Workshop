#include <stdio.h>
#include <stdlib.h> 

int main(int argc, const char *argv[])
{
    int correct = 0;
    char bof[64];

    scanf("%s",bof);

    if(correct != 0xdeadbeef)
    {
        puts("you suck!\n");
        exit(0);
    }
    puts("you win!\n");
    system("/bin/sh");

    return 0;
}
