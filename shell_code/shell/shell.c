#include <stdio.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    char buf[100];
    printf("buf: %x\n",buf);
    fflush(stdout);
    scanf("%s",buf);
    puts("returning NOW");
    
    return 0;
}
