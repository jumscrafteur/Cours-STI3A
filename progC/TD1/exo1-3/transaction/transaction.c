#include "transaction.h"
#include "globs.h"

float total = 0.0;
short count = 0;
short tax_percent = 6;
float add_with_tax(float f)
{
  float tax_rate = 1 + tax_percent / 100.0;
  total = total + (f * tax_rate);
  count = count + 1;
  return total;
}