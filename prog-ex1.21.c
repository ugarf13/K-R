/* Program to replace strings of blanks by the minimum number of tabs and blanks
 * to achieve the same spacing */

#include <stdio.h>

#define MAXLINE  1000 /* max char length of a line */
#define TABSPACE 8    /* number of tab stops */

int main (void)
{
    char  c;       /* char var to store current char */
    int   nb = 0;  /* number of blanks */
    int   nt = 0;  /* number of tabs */
    int   pos = 1; /* current position */

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
            /* update pos to current pos + number of spaces until next tab */
            pos = pos + TABSPACE - (pos -1) % TABSPACE;
            nb = 0; /* spaces from previous tab column don't matter anymore */
        } else { /* if current char is not a blank or tab, it's time to fill in blanks */
            /* no need to consider pos, as already taken care of before */

            /* put in tabs first, if any */
            while ( nt > 0 ) {
                putchar('\t');
                --nt;
            }
            /* next, put in the remaining blanks, if any */
            while ( nb > 0 ) {
                putchar(' ');
                --nb;
            }
            putchar(c); /* put it current non blank/tab char */
            ++pos; /* update current position */
            if ( c == '\n' ) /* if newline, restart from pos = 1 */
                pos = 1; /* no need to restart nb or nt as already re-initialized */
        }
    }

    return 0;
}





