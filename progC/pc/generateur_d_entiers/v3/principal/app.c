#include "suite.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int n = argc > 1 ? atoi(argv[1]) : 0;

    printf("des suites de symbole(s): \n");
    while (n-- > 0)
        suite_e_suite(n);

    printf("\n");
    return EXIT_SUCCESS;
}