#include <stdio.h>
#include "transaction.h"
#include "globs.h"

int main(void)
{
  float val;
  printf("Price of item: ");
  while (scanf("%f", &val) == 1)
  {
    printf("Total so far: %.2f\n", add_with_tax(val));
    printf("Price of item: ");
  }
  printf("\nFinal total: %.2f\n", total);
  printf("Number of items: %hi\n", count);
  return 0;
}
