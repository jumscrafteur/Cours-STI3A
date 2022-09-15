#include "transaction.h"

float add_with_tax(float f)
{
  float tax_rate = 1 + tax_percent / 100.0;

  total = total + (f * tax_rate);
  count = count + 1;
  return total;
}