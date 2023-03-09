#include <stdio.h>

int cp(char *source, char *dest)
{
    FILE *fp1, *fp2;

    fp1 = fopen(source, "r");
    fp2 = fopen(dest, "w");

    char c = fgetc(fp1);
    while (c != EOF)
    {
        fputc(c, fp2);
        c = fgetc(fp1);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
