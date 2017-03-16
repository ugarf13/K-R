/* Program that deletes each character in s1 that matches any character in the
 * string s2 */

#include <stdio.h>

#define YES 1
#define NO  0

void  squeeze( char  s1[], char  s2[] )
{
    int i, j, k; /* index list */
    int isAllowedChar; /* flag for whether a char is allowed */

    for ( i = 0, j = 0; s1[i] != '\0'; ++i ) {
        isAllowedChar = YES; /* compare s1[i] to each char in s2 */
        for ( k = 0; s2[k] != '\0'; ++k ) {
            if ( s1[i] == s2[k] ) {
                isAllowedChar = NO; /* match found */
                break;
            }
        }
        //printf("%i\n", isAllowedChar);
        if ( isAllowedChar ) /* if no match */
            s1[j++] = s1[i]; /* add char at position j */
    }
    s1[j] = '\0';
}


int main (void)
{
    char  s1[] = "hello world";
    char  s2[] = "ho";
    void  squeeze( char  s1[], char  s2[] );

    printf("string: \"%s\", list of forbidden chars: \"%s\"\n", s1, s2);

    squeeze(s1, s2);
    printf("Squeezed string: \"%s\"\n", s1);

    return 0;
}








