#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int x = 0;

    puts("give me an integer\n");
    fflush(stdout);
    if(scanf("%d",&x))
        puts("good job!");
    else
        puts("try again");

    return 0;
}
