#include <stdio.h>

int touch(char *filePath)
{
    FILE *fp = fopen(filePath, "w");

    if (fp != NULL)
    {
        fclose(fp), fp = NULL;
    }

    return 0;
}
