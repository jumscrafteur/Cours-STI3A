#include "tri3generic.h"

void tri3generic_tri(int *c1, int *c2, int *c3)
{

    if (*c1 > *c2)
        ECHANGE(c1, c2);
    if (*c2 > *c3)
        ECHANGE(c2, c3);

    if (*c1 > *c2)
        ECHANGE(c1, c2);
}