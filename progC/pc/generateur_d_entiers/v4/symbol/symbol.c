#include "symbol.h"
//generate
#include "generator.h"
//malloc
#include <stdlib.h>
//sprintf
#include <stdio.h>

#define PREFIX "FR__"
#define SUFFIX "_"
char *new_symbol(void)
{
    int n = generate();
    char *buffer = malloc(81 * sizeof(char));
    sprintf(buffer, "%s%d%s", PREFIX, n, SUFFIX);
    return buffer;
}