#include <stdio.h>

int head(char *filePath, int lineCount)
{
    int lineCountPassed = 0;

    FILE *fp = fopen(filePath, "r");

    char c = fgetc(fp);

    while (c != EOF)
    {
        if (c == '\n')
            lineCountPassed++;

        if (lineCountPassed == lineCount)
            break;

        printf("%c", c);
        c = fgetc(fp);
    }

    printf("\n");

    fclose(fp);

    return 0;
}
