/* Program to return the position of the rightmost occurrence of t in s, or -1
 * if there is none */

#include <stdio.h>

#define  MAXLINE  100 /* maximum length of string */

int  main (void)
{
    char  source[] = "hello world, this is a great world, the best world of all";
    char  pattern[] = "world";
    int   strrindex (char source[], char pattern[]);

    printf("%s\n", source);
    printf("Last match found at position %i\n", strrindex(source, pattern));

    return 0;
}



/* strrindex: return index of rightmost occurrence of pattern in source */
int  strrindex (char source[], char pattern[])
{
    int  i, j, k;
    int  index;

    for ( i = 0; source[i] != '\0'; ++i ) {
        for ( j = i, k = 0; pattern[k] != '\0' && pattern[k] == source[j]; ) {
            ++j; ++k; /* continue checking as long as chars match */
        }

        if ( k > 0 && pattern[k] == '\0' ) /* was the entire pattern matched ? */
            index = i;
    }

    return (index >= 0) ? index : -1;
}


