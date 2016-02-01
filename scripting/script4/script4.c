#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



int main(int argc, const char *argv[])
{
    int i,y,x;
    

    srand(time(NULL));
    for (i = 0; i < 10; i++) {
        x = 0;
        x = rand();
        printf("give me %8x\n",x);
        
        fflush(stdout);
        scanf("%d",&y);
        if (x == y) {
            continue;
        }else
        {
            printf("nope!\n");
            exit(0);
        }
    }
    printf("good job!\n");
    return 0;
}
