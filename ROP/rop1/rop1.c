#include <stdio.h>
#include <stdlib.h> 

void win()
{
    puts("you Win!\n");
    system("/bin/sh");
}

void func()
{
    
    int correct = 0;
    char bof[64];

    scanf("%s",bof);


    if(correct != 0xdeadbeef)
    {
        puts("you suck!\n");
        exit(0);
    }

}

int main()
{
    func();
    return 0;
}
