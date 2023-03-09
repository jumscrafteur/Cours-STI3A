#include <stdio.h>
#include <string.h>

int grep(char *filePath, char *match)
{

    FILE *fp = fopen(filePath, "r");

    char buffer[100];
    int bufferIndex = 0;
    int matchIndex = 0;
    int send = 0;

    char c = fgetc(fp);

    while (c != EOF)
    {
        buffer[bufferIndex] = c;

        bufferIndex++;

        if (c == '\n')
        {
            buffer[bufferIndex] = '\0';
            bufferIndex = 0;

            if (send == 1)
                printf("%s", buffer);

            send = 0;
        }

        if (c == match[matchIndex])
            matchIndex++;

        if (matchIndex == strlen(match))
            send = 1;

        c = fgetc(fp);
    }

    buffer[bufferIndex] = '\0';

    if (send == 1)
        printf("%s\n", buffer);

    fclose(fp);
    return 0;
}