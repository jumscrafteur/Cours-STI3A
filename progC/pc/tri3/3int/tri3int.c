#include "tri3int.h"
static void echange(int *c1, int *c2)
{
    int c = *c1;
    *c1 = *c2;
    *c2 = c;
}

void tri3int_tri(int *c1, int *c2, int *c3)
{

    if (*c1 > *c2)
        echange(c1, c2);
    if (*c2 > *c3)
        echange(c2, c3);

    if (*c1 > *c2)
        echange(c1, c2);
}