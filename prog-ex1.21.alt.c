/* This is the same as prog-ex1.21.c. I modified it to print the tabs
 * to check whether that program actually does work */

#include <stdio.h>

#define MAXLINE  1000 /* max char length of a line */
#define TABSPACE 8    /* number of tab stops */

int main (void)
{
    char  c;       /* char var to store current char */
    int   nb = 0;  /* number of blanks */
    int   nt = 0;  /* number of tabs */
    int   pos = 1; /* current position */
    char  buffer[MAXLINE]; /* store current line */
    int   i = 0;   /* current position is actual char inserted in buffer */

    while ( (c = getchar()) != EOF ) {
        if ( c == ' ') {
            /* if in pos 8, 16,..., a new blank takes me to next tab */
            if ( pos % TABSPACE == 0 ) {
                nb = 0;
                ++nt;
                ++pos;
            } else { /* still within two tabs, so just keep track where we are */
                ++nb;
                ++pos;
            }
        } else if ( c == '\t') {
            ++nt;
            pos = pos + TABSPACE - (pos - 1) % TABSPACE;
            nb = 0; /* spaces from previous tab column don't matter anymore */
        } else { /* if current char is not a blank or tab, it's time to fill in blanks */
            while ( nt > 0 ) {
                buffer[i] = '\t';
                ++i;
                --nt;
            }

            while ( nb > 0 ) {
                buffer[i] = ' ';
                ++i;
                --nb;
            }
            buffer[i] = c;
            ++i;
            ++pos;
            if ( c == '\n' ) 
                break; /* move to print current line */
        }
    }

    buffer[i - 1] = '\0';
    for ( i = 0; buffer[i] != '\0'; ++i )
        if ( buffer[i] == '\t' )
            printf("%s", "\\t");
        else if ( buffer[i] == ' ' )
            printf("%s", "\\s");
        else
            printf("%c", buffer[i]);
    printf("\n");

    return 0;
}





