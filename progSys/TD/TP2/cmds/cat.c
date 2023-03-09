#include <stdio.h>

int cat(char *filePath)
{
    FILE *fp = fopen(filePath, "r");

    char c;

    c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }

    printf("\n");

    return 0;
}
