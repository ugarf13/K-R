#include <stdio.h>

#define  SIZE  30 /* max array size */

int   getch (void);
void  ungetch (int);

int main (void)
{
    int  n, m, array[SIZE], getint(int *);
    int  getint (int *);

    for ( n = 0; n < SIZE && getint(&array[n]) != EOF; ++n )
        ;

    printf("\n{");
    for ( m = 0; m < n; ++m )
        printf("%i, ", array[m]);
    printf("\b\b}\n");

    return 0;
}


#include <ctype.h>

/* getint: get next integer from input into *pn */
int  getint (int *pn)
{
    int  c, sign;

    while ( isspace(c = getch()) ) /* skip white space */
        ;
    if ( !isdigit(c) && c != EOF && c != '-' && c != '+' ) {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if ( c == '-' || c == '+' )
        c = getch(); /* move to next char */
    for ( *pn = 0; isdigit(c); ) { /* if c not digit, 0 is stored */
        *pn = 10 * (*pn) + (c - '0'); /* convert digit to int and store it*/
        c = getch();
    }
    *pn *= sign; /* put back in the sign */
    if ( c != EOF )
        ungetch(c);
    return c;
}



/* ************************************************* */
#define BUFSIZE  100

char  buf[BUFSIZE];  /* buffer for ungetch */
int   bufp = 0;      /* next free position in buf */

int  getch (void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void  ungetch (int c) /* push character back on input */
{
    if ( bufp >= BUFSIZE )
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}

