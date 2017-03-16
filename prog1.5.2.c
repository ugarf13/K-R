/* Program to count characters in input */

#include <stdio.h>

int main (void)
{
    long int  nc = 0;

    while ( getchar() != EOF )
        ++nc;

    printf("\nNumber of characters = %li\n", nc);

    return 0;
}

    
