
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
        [1]buf1 = malloc(256);
        [2]strcpy(buf1, argv[1]); /* Prereq 1 */
        [3]buf2 = malloc(strtoul(argv[2], NULL, 16)); /* Prereq 2 */
        [4]buf3 = malloc(256); /* Prereq 3 */
        [5]strcpy(buf3, argv[3]); /* Prereq 3 */

        [6]free(buf3);
        free(buf2);
        free(buf1);
        return 0;
}
