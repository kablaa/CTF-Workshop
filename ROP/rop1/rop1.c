#include <stdio.h>
#include <stdlib.h> 

void win()
{
    puts("you Win!\n");
    system("/bin/sh");
}
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

    return 0;
}
