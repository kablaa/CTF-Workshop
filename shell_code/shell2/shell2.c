#include <stdio.h>
#include <stdlib.h> 

int main(int argc, const char *argv[])
{
    int correct = 0;
    char bof[64];

    printf("0x%x\n",bof);

    fflush(stdout);
    scanf("%s",bof);

    if(correct != 0xdeadbeef)
    {
        puts("you suck!\n");
        exit(0);
    }

    return 0;
}
