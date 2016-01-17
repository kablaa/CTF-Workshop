#include <stdio.h>
#include <stdlib.h>


void welcome(char *name)
{
    printf("greetings, ");
    printf(name);
}

void auth()
{
    char pass[50];
    printf("\nenter your password : ");
    fflush(stdout);
    scanf("%s",pass);
    printf("now go fuck yourself\n");
}

int main(int argc, const char *argv[])
{

    char name[50];

    puts("enter your name:");
    fflush(stdout);

    fgets(name,sizeof(name),stdin);
    welcome(name);
    auth();

    return 0;
}
