#include <stdbool.h>
#include "mathematika.h"
int mathematika_gcd(int x, int y)
{
    if (x == 0)
    {
        return y;
    }
    return mathematika_gcd(y % x, x);
}

bool mathematika_isPrime(int n)
{
    for (int i = 2; i * i < n + 1; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool mathematika_isCoPrime(int x, int y)
{
    return mathematika_gcd(x, y) == 1;
}
