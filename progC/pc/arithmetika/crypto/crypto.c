#include "crypto.h"

void crypto_encrypt(char *message)
{
    char c;
    while (*message)
    {
        *message = *message ^ 31;
        message++;
    }
}