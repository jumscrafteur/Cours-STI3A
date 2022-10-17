#include "generator.h"
#define INITIAL_VALUE 1
#include <stdio.h>
int generator_generate(message m)
{

    static int val = INITIAL_VALUE;
    switch (m)
    {
    case Debut:
        val = INITIAL_VALUE;
        return 0;
    case Suivant:
        return val++;
    default:
        printf("problemo");
        break;
    }
    return 0;
}
