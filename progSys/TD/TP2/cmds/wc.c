#include <stdio.h>

int wc(char *filePath)
{
    FILE *fp = fopen(filePath, "r");

    int wordCount = 1;

    char c = fgetc(fp);
    while (c != EOF)
    {
        if (c == ' ' || c == '\n')
            wordCount++;

        c = fgetc(fp);
    }

    printf("%d\n", wordCount);

    return 0;
}