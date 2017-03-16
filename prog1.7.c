/* Program to compute power of an int to an int */

#include <stdio.h>

/* power function */
int  power ( int base, int n )
{
    int i, result = 1;

    for ( i = 1; i <= n; ++i )
        result *= base;

    return result;
}

int main (void)
{
    int  power ( int base, int n );
    int  base, n;

    base = -5;
    n = 2;

    printf("%i^%i = %i\n", base, n, power(base, n));

    return 0;
}
