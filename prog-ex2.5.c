/* Program which returns the first location in the string s1 where any character
 * from the string s2 occurs, or -1 if s1 contains no characters from s2 */

#include <stdio.h>

int  any ( char s1[], char s2[] )
{
    int  i, j;
    //int  found = NO;
    
    for ( i = 0; s1[i] != '\0'; ++i ) {
        for ( j = 0; s2[j] != '\0'; ++j ) {
            if ( s1[i] == s2[j] ) 
                return i;
        }
    }

    return -1;
}

int main (void)
{
    char  s1[] = "hello, world";
    char  s2[] = "r";
    int   index;
    int   any ( char s1[], char s2[] );
    
    index = any(s1, s2);

    if ( index > -1 )
        printf("first occurance is at index = %i\n", index);
    else
        printf("Not found!\n");

    return 0;
}


