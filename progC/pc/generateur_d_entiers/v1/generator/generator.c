#include "generator.h"
#define INITIAL_VALUE 0
int generator_generate(void)
{
    //val est une v.l de classe statique
    static int val = INITIAL_VALUE;
    return val++;
}