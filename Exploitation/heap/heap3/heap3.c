
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
        char *buf1, *buf2, *buf3;
        if (argc != 4) {
                printf("Usage Error\n");
                return;
        }
        buf1 = malloc(256);
        strcpy(buf1, argv[1]);
        buf2 = malloc(strtoul(argv[2], NULL, 16));
        buf3 = malloc(256);
        strcpy(buf3, argv[3]);

        free(buf3);
        free(buf2);
        free(buf1);
        return 0;
}
