#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char *argv[])
{
    int x = 0;
    int y = 0;

    srand(time(NULL));
    x = rand();

    printf("give me %d\n",x);
    fflush(stdout);
    scanf("%d",&y);
    if(x == y)
        puts("good job!");
    else 
        puts("try again");
    
    return 0;
}
