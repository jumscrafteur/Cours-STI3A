#include "suite.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n = argc > 1 ? atoi(argv[1]) : 0;

    generator_generate(Pas, -2);
    generator_generate(Premier, n);
    printf("des suites arithmétiques: \n");
    while (n-- > 0)
    {
        suite_e_suite(n);
        putchar('\n');
    }
    printf("\n");
    return EXIT_SUCCESS;
}