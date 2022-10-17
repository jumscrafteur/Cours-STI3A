#include <stdio.h>
#include "suite.h"
#include "generator.h"

//Adapter ce module à la nouvelle version du générateur d'entiers

void e_suite(int longueur)
{

    generate(Debut);
    printf("(");
    while (longueur-- >= 0)
    {
        printf("%d , ", generate(Suivant));
    }
    printf(")");
}
