#include <stdio.h>

int tail(char *filePath, int lineCount)
{
    char lines[lineCount][100];

    int lineIndex = 0;
    int rowIndex = 0;

    FILE *fp = fopen(filePath, "r");

    char c;

    c = fgetc(fp);
    while (c != EOF)
    {
        lines[rowIndex % lineCount][lineIndex] = c;

        lineIndex++;

        if (c == '\n')
        {
            lines[rowIndex % lineCount][lineIndex] = '\0';
            rowIndex++;
            lineIndex = 0;
        }

        c = fgetc(fp);
    }

    for (size_t i = 0; i < lineCount; i++)
    {
        // printf("%d", i);
        printf("%s", lines[(rowIndex + i) % lineCount]);
    }

    // printf("%s", lines[1]);

    fclose(fp);

    return 0;
}