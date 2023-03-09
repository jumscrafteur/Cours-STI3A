#include <stdio.h>

int clean(char *filePath)
{
    FILE *fp = fopen(filePath, "w");

    fclose(fp);

    return 0;
}