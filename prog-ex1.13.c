/* Program to count lines, words, and chars in input */

#include <stdio.h>

#define IN      1  /* inside a word */
#define OUT     0  /* outside a word */
#define MAXWORD 11 /* max length of word */

int main (void)
{
    int  c, i, j, nc = 0;
    int  state; /* flag for in or outside a word */
    int  ovflow; /* count number of words which exceed MAXWORD */
    int  freq[MAXWORD];

    for ( i = 0; i < MAXWORD; ++i)
        freq[i] = 0;

    state = OUT;

    while ( ( c = getchar() ) != EOF )
    {
        if ( c == '\n' || c == ' ' || c == '\t' )
        { /* separator is at the end a word */ 
            if ( state == IN )
            {
                state = OUT; /* we are outside a word / we are looking for a word */
                if ( nc < MAXWORD)
                    ++freq[nc]; /* nc is length of current word, increment approp freq */
                else
                    ++ovflow;
                nc = 0; /* restart the counter for number of chars */
            }
        }
        else if ( state == OUT ) /* c is a alphanum and we are looking for a word */
        {
            state = IN;
            ++nc;
        }
        else
            ++nc;
    }
    
    printf("\n");

    for ( i = 1; i < MAXWORD; ++i ) 
    {
        //if ( freq[i] != 0 )
        printf("len %2i = %i: ", i, freq[i]); 
        for ( j = 1; j <= freq[i]; ++j)
            printf("*");
        printf("\n");
    }

    printf("\noverflow = %i\n", ovflow);

    return 0;
}
