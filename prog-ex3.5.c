/* Program to convert an integer n into a base b character representation */

#include <stdio.h>
#include <string.h>

int  main (void)
{
    int   n = 255;
    int   b = 16;
    char  s[100];
    void  itob (int n, char s[], int b);

    printf("%i = ", n);
    itob(n, s, b);
    printf("%s in base %i\n", s, b);

    return 0;
}


void  itob (int n, char s[], int b)
{
    int   i, sign;
    char  digit;
    void  reverse (char s[]);
    int  abs (int n);

    if ( b < 2 || b > 16 ) {
        printf("Invalid base.\n");
        return;
    }

    sign = n; /* store original number with sign */

    i = 0;
    do {
        digit = abs(n % b);
        s[i++] = (digit > 10 ) ? (digit - 10 + 'a') : (digit + '0');
    } while ( (n /= b) != 0 );
    
    if ( b == 16 ) {
        s[i++] = 'x';
        s[i++] = '0';
    }
    if ( sign < 0 )
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

void  reverse (char s[])
{
    int  i, j;

    for ( i = 0, j = strlen(s) - 1; i < j; ++i, --j ) {
        s[i] ^= s[j];
        s[j] ^= s[i];
        s[i] ^= s[j];
    }
}

int  abs (int n)
{
    return (n < 0) ? -n : n;
}

