#include "new_lib.h"
#include <unistd.h>

int ind = -1;
char buffer;

void *new_malloc(int size)
{
  void *pointer = sbrk(0)
}