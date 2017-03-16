/* Program to count lines, words, and chars in input */

#include <stdio.h>

#define IN  1 /* inside a word */
#define OUT 0 /* outside a word */

int main (void)
{
    int  c, nl, nc, nw;
    int  state; /* flag for in or outside a word */


    state = OUT;
    nl = 0; nc = 0; nw = 0;

    while ( ( c = getchar() ) != EOF )
    {
        ++nc;
        if ( c == '\n' )
            ++nl;
        if ( c == '\n' || c == ' ' || c == '\t' )
            state = OUT; /* we are outside a word / we are looking for a word */
        else if ( state == OUT ) /* c is a alphanum and we are looking for a word */
        {
            ++nw;
            state = IN;
        }
    }

    printf("\nnl = %i, nc = %i, nw = %i\n", nl, nc, nw);

    return 0;
}
