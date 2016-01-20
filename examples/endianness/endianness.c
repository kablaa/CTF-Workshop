#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int x = 0x6861636b;
    char str[5] = {0x68,0x61,0x63,0x6b,'\0'};
    printf("%s\n",str);

    int i;
    //here we are assigning a character pointer to the address of an integer. When we increment the pointer, it will be incremented by one byte, because that is the size of a character. 
    char *p = (char*)&x;
    for (i = 0; i < 4; i++,p++) {
        printf("%c",(char)*p);
    }
    puts("\n");
    return 0;
}
