#include <stdio.h>
#include <stdbool.h>

#define  SIZE       30 /* max array size */
#define  MIN(A,B)   ( ((A) > (B)) ? (B) : (A) )

bool  isNum; /* flag to check whether a zero is a number or not*/
int   getch (void);
void  ungetch (int);

int main (void)
{
    int   n, test, array[SIZE], getint(int *);
    int   count;
    int   getint (int *);

    for ( n = 0; n < SIZE; ) {
        if ( (test = getint(&array[n])) == 0 ) { /* not a number or EOF*/
            getch(); /* remove it */
            continue; /* let's move on */
        } else if ( test > 0 )  /* number found */
            ++n;
        else {   /* EOF */
            if ( isNum ) /* is last 0 put into array an actual number? */
                ++n;
            break;
        }
    }

    printf("\n");
    for ( count = 0; count < n;  ++count )
        printf("%i ", array[count]);
    printf("\n");

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
    isNum = false; /* if c is EOF, *pn is set to 0 but not actual number */
    sign = (c == '-') ? -1 : 1;
    if ( c == '-' || c == '+' )
        c = getch(); /* move to next char */
       
    for ( *pn = 0; isdigit(c); ) { /* if c not digit, 0 is stored */
        isNum = true;
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

