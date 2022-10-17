#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int n = argc > 1 ? atoi(argv[1]) : 0;
    char *ns;
    printf("la suite de %d symbole(s): \n", n);
    while (n-- > 0)
    {
        ns = symbol_new_symbol();
        printf("%s\n", ns);
    }
    free(ns);
    printf("\n");
    return EXIT_SUCCESS;
}