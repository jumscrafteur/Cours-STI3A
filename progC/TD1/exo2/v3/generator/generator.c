#include "generator.h"
#define INITIAL_VALUE 1
#include <stdio.h>

int generator_generate(message m)
{

  // val est une v.l de classe statique
  static int val = INITIAL_VALUE;
  switch (m)
  {
  case Debut:
    val = INITIAL_VALUE;
    return 0;
  case Suivant:
    return val++;
  default:
    printf("Erreur");
    break;
  }
  return 0;
}