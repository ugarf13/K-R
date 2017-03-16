/* Program to count lines, words, and chars in input */

#include <stdio.h>

#define IN  1 /* inside a word */
#define OUT 0 /* outside a word */

int main (void)
{
    int  c;
    int  state; /* flag for in or outside a word */


    state = OUT;

    while ( ( c = getchar() ) != EOF )
    {
        if ( c == '\n' || c == ' ' || c == '\t' )
        { /* insert newline only if separator is at the end a word */ 
            if ( state == IN )
            {
                state = OUT; /* we are outside a word / we are looking for a word */
                putchar('\n');
            }
        }
        else if ( state == OUT ) /* c is a alphanum and we are looking for a word */
        {
            state = IN;
            putchar(c);
        }
        else
            putchar(c);
    }

    return 0;
}
