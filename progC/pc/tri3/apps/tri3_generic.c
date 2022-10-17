#include <stdio.h>
#include <stdlib.h>
#include "tri3generic.h"
// gcc I../3generic -o tri3_generic
int main()
{
    char c1 = 'z';
    char c2 = 'x';
    char c3 = 'y';
    TRI(c1, c2, c3, char);
    printf("%c %c %c\n", c1, c2, c3);
    int j1 = 3;
    int j2 = 2;
    int j3 = 1;
    TRI(j1, j2, j3, int);
    printf("%d %d %d\n", j1, j2, j3);
    return EXIT_SUCCESS;
}
