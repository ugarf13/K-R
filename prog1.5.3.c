/* Program to count lines */

#include <stdio.h>

int main (void)
{
    int c, nl;

    while ( ( c = getchar() ) != EOF )
        if ( c == '\n' )
            ++nl;

    printf("\nNumber of lines = %i\n", nl);

    return 0;
}

