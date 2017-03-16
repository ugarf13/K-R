/* reverse Polish calculator */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <math.h>     /* include math functions */
#include <string.h>   /* for strcmp() */

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */
#define NAME     'n'  /* signal that a name was found */


int     getop (char s[]);
void    push  (double f);
double  pop   (void);
double  mathFunc (char s[]);

int  main (void)
{
    int     type;
    double  op2;
    char    s[MAXOP];

    while ( (type = getop(s)) != EOF ) {
        //printf("%s\n", s);
        switch ( type ) {
            case NUMBER:
                push(atof(s)); /* convert number to float and push onto stack */
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if ( op2 != 0.0 )
                    push(pop() / op2);
                else
                    printf("Error: Zero division.\n");
                break;
            case NAME: /* name was found */
                mathFunc(s);
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("Error: Unknown command.\n");
        }
    }

    return 0;
}

/* mathfunc: apply math function specified by s to f */
double  mathFunc (char s[])
{
    double op2;

    if ( strcmp(s, "exp") == 0 ) 
        push(exp(pop()));
    else if ( strcmp(s, "pow") == 0 ) { 
        op2 = pop();
        push(pow(pop(), op2));
    } else if ( strcmp(s, "sin") == 0 )
        push(sin(pop()));
    else 
        printf("Error: %s is not an allowed function.\n", s);
}

/* ************************************************ */
/* Define stack an operators on the stack */

#define MAXVAL   100  /* maximum depth of val stack */

int  sp = 0;          /* next free stack position */
double val[MAXVAL];   /* value stack */

/* push: push f onto the stack */
void  push (double f)
{
    if ( sp < MAXVAL )  /* still free space on the stack */
        val[sp++] = f;
    else 
        printf("Error: Stack full, can't push %g.\n", f);
}


/* pop: pop and return top value from stack */
double  pop (void)
{
    if ( sp > 0 )
        return val[--sp];
    else {
        printf("Error: Stack empty.\n");
        return 0.0;
    }
}


/* ******************************************** */

#include <ctype.h>

int   getch (void);
void  ungetch (int);

/* getop: get next operator or numeric operand */
int  getop (char s[])
{
    int  i, c;

    while ( (s[0] = c = getch()) == ' ' || c == '\t' )
        ;
    s[1] = '\0';
    i = 0;
    if ( isalpha(c) ) {
        while ( isalpha(s[++i] = c = getch()) )
            ;
        s[i] = '\0';
        if ( c != EOF )
            ungetch(c);
        if ( i == 1 && s[0] != '-' ) /* only one char was collected, not a minus */
            return s[0]; /* could be an operator or \n */
        else if ( i > 1 )
            return NAME;
    }

    if ( !isdigit(c) && c !=  '-' ) 
        return c; /* must be an operator */

    if ( c == '-' ) {
        if ( isdigit(c = getch()) || c == '.' )
            s[++i] = c; /* it's negative number */
        else {          /* it's a minus operator */
            if ( c != EOF )
                ungetch(c);
        return '-';
        }
    }
    
    if ( isdigit(c) ) /* collect integer part */
        while ( isdigit(s[++i] = c = getch()) )
            ;
    if ( c == '.' )   /* collect fraction part */
        while ( isdigit(s[++i] = c = getch()) )
            ;
    s[i] = '\0';
    if ( c != EOF )
        ungetch(c);
    return NUMBER;
}


/* ********************************************* */

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


