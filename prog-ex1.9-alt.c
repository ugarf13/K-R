/* Program to copy input to output which replaces string of multiple blanks with
 * a single one */

#include <stdio.h>

#define NONBLANK 'e'

int main (void)
{
    int  c;
    int  last_c = NONBLANK;

    while ( ( c = getchar() ) != EOF )
    {
        if ( c != ' ' )
            putchar(c);
        if ( c == ' ' )
            if ( last_c != ' ' )
                putchar(c);
        last_c = c;
    }

    return 0;
}


