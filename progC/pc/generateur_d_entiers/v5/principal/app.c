#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

static void iterate(int first, int step, int size)
{
    generator_define_first(first);
    generator_define_step(step);
    generator_go_to_beginning();

    while (size-- > 0)
        printf("%d,", generator_get_next());
}
int main(int argc, char **argv)
{
    long int max = argc > 1 ? strtol(argv[1], NULL, 10) : 1;

    printf("des suites : \n");
    for (long int i = 1; i <= max; i++)
    {
        iterate(1, 1, i);
        iterate(i - 1, -1, i - 1);
        putchar('\n');
    }

    return EXIT_SUCCESS;
}