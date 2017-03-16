/* Program to count lines */

#include <stdio.h>

int main (void)
{
    int c, nl = 0, ns = 0, nt = 0;

    while ( ( c = getchar() ) != EOF )
        if ( c == '\n' )
            ++nl; 
        else if ( c == ' ' )
            ++ns;
        else if ( c == '\t' )
            ++nt;

    printf("\nNumber of newlines = %i\n", nl);
    printf("Number of spaces = %i\n", ns);
    printf("Number of tabs = %i\n", nt);

    return 0;
}

