#include <stdio.h>
#define  MAXLINE  80  /* maximum number of lines */

int main (void)
{
    int   i;
    char  c;
    char  s[MAXLINE];

    for ( i = 0; i < MAXLINE - 1; ++i ) {
        if ( (c = getchar()) == '\n') 
            break;
        else if ( c == EOF ) {
            putchar('\n');
            break;
        } else 
            s[i] = c;
    }

    s[i] = '\0';

    printf("%s\n", s);

    return 0;
}


            
