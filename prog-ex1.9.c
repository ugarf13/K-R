/* Program to copy input to output which replaces multiple blanks
 * with a single blank */

#include <stdio.h>

int main (void)
{
    int  c;
    int  nb = 0; /* number of blanks already printed since last nonblank */


    while ( ( c = getchar() ) != EOF )
        if ( c != ' ' )
        {
            putchar(c);
            nb = 0;
        }
        else if ( nb == 0 ) /* if here c must be blank */
        {
            putchar(c);
            nb = 1;
        }

    return 0;
}

