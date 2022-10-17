#include <stdio.h>
#include "mathematika.h"
#include "crypto.h"
int main()
{
    printf("Co-Prime Checker!\n");

    int x, y;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &x, &y);

    if (mathematika_isCoPrime(x, y))
    {
        printf("The 2 numbers are co-prime!\n");
    }
    else
    {
        printf("The 2 numbers are not co-prime\n");
    }

    printf("GCD of the 2 numbers is: %d\n", mathematika_gcd(x, y));
    char secret[1400];

    printf("Encrypt a secret : ");
    //scanf("%s", secret);
    scanf("\n");
    fgets(secret, 1400, stdin);
    crypto_encrypt(secret);
    printf("my encrypted secret is : %s\n", secret);
    return 0;
}