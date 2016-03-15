#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void uncalled(char *arg)
{
    system(arg);
}

void place()
{
    int buff[10]= {0};
    int i,j, index,value;
    for (j = 0; j < 10; j++) {
        
        puts("enter index");
        fflush(stdout);
        scanf("%d",&index);
        puts("enter value");
        fflush(stdout);
        scanf("%d", &value);
        if(index > 9)
            exit(0);
        buff[index] = value;
    }
        
    puts("behold, your creation!");
    fflush(stdout);
    for (i = 0; i < 10; i++) {
        printf("%d ",buff[i]);
        fflush(stdout);
    }

}


void greetings()
{
    char name[10];
    puts("What should I call you? ");
    fflush(stdout);
    scanf("%9s",name);
    printf("Welcome %s! This is the interactive array builder, where you decide what goes where!\n",name);
    fflush(stdout);
}

int main(int argc, const char *argv[])
{

    greetings();
    place();

    return 0;
}
