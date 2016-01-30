#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char buf[64];
    fgets(buf, 64, stdin);
    printf("%s\n",buf);
    return 0;
}
