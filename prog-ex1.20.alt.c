/* Program which replaces tabs with equivalent number of blank spaces to the
 * next tab stop */

#include <stdio.h>

#define MAXLINE   1000 /* maximum length of a line */
#define TABSPACE  8    /* number of characters between consecutive tab stops */

int main (void)
{
    int   c;   /* store current char */
    int   nb;  /* number of blank spaces */
    int   pos; /* current position */
    char  buffer[MAXLINE]; /* store current line */
    int   i;   /* current position in buffer */

    i = 0;
    pos = 1;

    while ( (c = getchar()) != EOF ) {
        if ( c == '\t' ) {
            /* number of blank space to reach next tab stop */
            nb = TABSPACE - (pos - 1) % TABSPACE;

            /* replace tab with equivalent number of blank spaces */
            while ( nb > 0 ) {
                putchar(' ');
                --nb;
                buffer[i] = ' ';
                ++pos;
                ++i;
            } 
        } else {
            putchar(c);
            ++pos;
            buffer[i] = c;
            ++i;

            if ( c == '\n' )
                break; /* I can only enter one line but it's fine */
        }
    }
    buffer[i] = '\0';

    for ( i = 0; buffer[i] != '\0'; ++i ) {
        if ( buffer[i] == ' ')
            printf("%s", "\\s");
        else 
            printf("%c", buffer[i]);
    } 
    
    return 0;

}


