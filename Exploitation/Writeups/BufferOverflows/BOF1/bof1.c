#include <stdio.h>
#include <stdlib.h> 

int main(int argc, const char *argv[])
{
    int correct = 0;
    char bof[64];

    scanf("%s",bof);

    if(correct != 0)
    {
        puts("you win!");
        system("/bin/sh");
    }
    return 0;
}
