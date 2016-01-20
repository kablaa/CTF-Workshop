#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char x;

    puts("give me a NOP");
    fflush(stdout);

    scanf("%c",&x);

    if(x ==(char)0x90)
        puts("good job");
    else
        printf("%c\n", x);

    return 0;
}
