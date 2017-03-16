/* Program to copy input to output which replaces tabs with \t, backspaces with
 * \b, and backslashes with \\ */

#include <stdio.h>

#define NONBLANK 'e'

int main (void)
{
    int  c;
    int  last_c = NONBLANK;

    while ( ( c = getchar() ) != EOF )
    {
        if ( c == ' ' )
        {
            if ( last_c != ' ' )
                putchar(c);
        }
        else if ( c == '\t' )
            printf("\\t");
        else if ( c == '\b' )
            printf("\\b");
        else if ( c == '\\' )
            printf("\\\\");
        else
            putchar(c);
        last_c = c;
    }

    return 0;
}


