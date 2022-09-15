#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int n = argc > 1 ? atoi(argv[1]):0;

  printf("La suite de %d nombre(s)\n", n);
  while(n-- >0)
  {
    printf("%d,",generator_generate());
  }
  printf("\n");
  return EXIT_SUCCESS;
}