#include <stdio.h>
#include <stdlib.h>
#include "tri3car.h"
#include "tri3int.h"

// gcc ../3int/tri3int.o ../3car/tri3car.o tri3_duplicate.o -o tri3_ducplicate
int main()
{

    char c1 = 'z';
    char c2 = 'x';
    char c3 = 'y';
    tri3car(&c1, &c2, &c3);
    printf("%c %c %c\n", c1, c2, c3);

    int j1 = 3;
    int j2 = 2;
    int j3 = 1;
    tri3int(&j1, &j2, &j3);
    printf("%c %c %c\n", c1, c2, c3);
    return EXIT_SUCCESS;
}
