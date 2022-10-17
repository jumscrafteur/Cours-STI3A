#include "symbol.h"
//generate
#include "generator.h"
//malloc
#include <stdlib.h>
//sprintf
#include <stdio.h>
#define PREFIX "FR__"
#define SUFFIX "_"

char *symbol_new_symbol(void)
{
    int n = generator_generate();

    static char *buffer = NULL;
    if (buffer == NULL)
        buffer = malloc(81 * sizeof(char));
    sprintf(buffer, "%s%d%s", PREFIX, n, SUFFIX);
    return buffer;
}