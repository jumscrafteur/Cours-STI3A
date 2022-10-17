#include "tri3car.h"
static void echange(char *c1, char *c2)
{
    char c = *c1;
    *c1 = *c2;
    *c2 = c;
}

void tri3car_tri(char *c1, char *c2, char *c3)
{

    if (*c1 > *c2)
        echange(c1, c2);
    if (*c2 > *c3)
        echange(c2, c3);

    if (*c1 > *c2)
        echange(c1, c2);
}