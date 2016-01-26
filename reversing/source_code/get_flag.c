#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void winner()
{
    puts("Congratulations");
}

void pass2(char * input)
{
    char *p = input;
    p+=10;
    system(p);
}


void pass1(char *input)
{
   if(!strncmp(input,"iamahacker",10))
   {
        pass2(input);
   }
   else
       puts("try again");
}

int main()
{
    char buff[64];
    read(0,buff,sizeof(buff));
    pass1(buff);
    return 0;
}
