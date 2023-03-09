#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
int main()
{
    int argReadIndex = 0;
    int argCount = 0;
    int fullLen = 0;

    char *args[100];
    char fullCmd[1000];

    args[0] = calloc(100, sizeof(char));

    char actualChar = fgetc(stdin);

    while (1)
    {
        if (actualChar == '\n')
        {
            fullCmd[fullLen] = '\0';
            argCount++;
            break;
        }

        if (actualChar == ' ')
        {
            args[argCount][argReadIndex + 1] = '\0';
            argCount++;
            args[argCount] = calloc(100, sizeof(char));
            argReadIndex = 0;
        }
        else
        {
            args[argCount][argReadIndex] = actualChar;
            argReadIndex++;
        }

        fullCmd[fullLen] = actualChar;
        fullLen++;
        actualChar = fgetc(stdin);
    }

    if (strcmp(args[0], "touch") == 0)
        touch(args[1]);
    else if (strcmp(args[0], "cp") == 0)
        cp(args[1], args[2]);
    else if (strcmp(args[0], "echo") == 0)
        echo(fullCmd + strlen("echo "));
    else if (strcmp(args[0], "cat") == 0)
        cat(args[1]);
    else if (strcmp(args[0], "head") == 0)
    {
        int lineCount = 0;
        for (int i = 1; i < argCount; i++)
        {
            if (strcmp("-n", args[i]) == 0 && (i + 1) < argCount)
            {
                lineCount = atoi(args[i + 1]);
            }
        }

        head(args[1], lineCount);
    }
    else if (strcmp(args[0], "tail") == 0)
    {
        int lineCount = 0;
        for (int i = 1; i < argCount; i++)
        {
            if (strcmp("-n", args[i]) == 0 && (i + 1) < argCount)
            {
                lineCount = atoi(args[i + 1]);
            }
        }

        tail(args[1], lineCount);
    }
    else if (strcmp(args[0], "clean") == 0)
        clean(args[1]);
    else if (strcmp(args[0], "grep") == 0)
        grep(args[1], args[2]);
    else if (strcmp(args[0], "wc") == 0)
        wc(args[1]);

    return 0;
}