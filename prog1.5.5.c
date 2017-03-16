/* Program to count digits, whitespaces, and other chars */

#include <stdio.h>

int main (void)
{
    int  c, i, nwhite, nother;
    int  ndigits[10];

    nwhite = 0; nother = 0;

    for ( i = 0; i < 10; ++i )
        ndigits[i] = 0;

    while ( ( c = getchar() ) != EOF )
    {
        if ( c >= '0' && c <= '9' )
            ++ndigits[c - '0'];
        else if ( c == ' ' || c == '\n' || c == '\t' )
            ++nwhite;
        else
            ++nother;
    }

    printf("\nnwhite = %i, nother = %i\n", nwhite, nother);

    for ( i = 0; i < 10; ++i)
        printf("count %i = %i\n", i, ndigits[i]);

    return 0;
}
