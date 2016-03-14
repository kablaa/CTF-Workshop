#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *hint = "/bin/sh";
void win_func(char* y)
{
        system(y);

}
void mem_test(char* p)
{
    char buff[11];

    memset(buff,'\0', sizeof(buff));

    printf("\nI know that mine is fine...see? : ");
    printf("0x%x \n",hint);

    puts("Let's see how good your memory is...\n");
    printf("> ");
    scanf("%s",buff);

       if(strncmp(buff,p,sizeof(p)))
       {
        puts("sorry, your memory sucks\n");
       }else
            puts("good job!!\n");

}

int main(int argc,  char *argv[])
{
    int len = 10;
    char random[11];
    int i;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";


    puts("\n\n\n------Test Your Memory!-------\n");

    srand(time (NULL));
    for (i = 0; i < len; ++i) {
        random[i] = alphanum[ rand() % (sizeof(alphanum) - 1)];
    }
    printf("%s",random);
    mem_test(random);

    return 0;
}
