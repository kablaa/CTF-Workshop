#include <stdio.h>
#include <stdlib.h>

void win()
{
    puts("you win!\n");
    system("/bin/sh");
}
void lose()
{
    puts("you suck!\n");
    exit(0);
}
int main(int argc, const char *argv[])
{
    void (*fp)(); 
    char bof[64];

    fp = &lose;

    scanf("%s",bof);
    fp();
    
    return 0;
}
