/* Program to convert an hexadecimal number to an decimal integer */

#include <stdio.h>

int  power ( int  x, int  n )
{
    int result = 1;

    if ( n == 0 )
        return 1;

    while ( n > 0 ) {
        result *= x;
        --n;
    }

    return result;
}

int  htoi ( int n )
{
    int  i; 
    int  rem, result;
    int  power ( int  x, int  n );
    
    result = 0;
    for ( i = 0; n != 0; ++i ) {
        rem = n % 16;
        result = result + rem * power(16, i);
        //printf("16^%i = %i\n", i, power(16, i));
        n = n / 16;
    }

    return result;
}


int main (void)
{
    int  n = '\xFF';
    int  htoi ( int x );

    printf("n in hex form = %x\n", n);
    
    printf("n in decimal form = %i\n", htoi(n));
   
    return 0;
}
