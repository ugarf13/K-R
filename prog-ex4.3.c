/* reverse Polish calculator */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <math.h>     /* for fmod() */

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */

int     getop (char s[]);
void    push  (double f);
double  pop   (void);
double  Abs (double f);
    

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
            case '%':
                op2 = pop();
                if ( op2 > 0.0 )
                    push( (int) pop() % (int) op2);
                else
                    printf("Error: Cannot perform modulus.\n");
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

double  Abs (double f)
{
    return (f < 0) ? -f : f;
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
    int  i, c, d;

    while ( (s[0] = c = getch()) == ' ' || c == '\t' )
        ; /* continue until we find something */
    s[1] = '\0';
    
    i = 0;
    if ( !isdigit(c) && c != '.' ) {
        if ( c == '-' || c == '+' ) {
            if ( isdigit(d = getch()) ) { /* c denotes a sign */
                s[++i] = d; /* c is already saved at s[0], so save d in next spot */
            } else if ( d != EOF ) { /* c is a not a sign */
                ungetch(d);  /* push d back */
                return c;    /* not a number */
            }
        } else
            return c;
    }

    if ( i > 0 ) {/* sign was found */
        if ( isdigit(s[++i] = c = getchar()) ) { /* continue to collect integer part */
            while ( isdigit(s[++i] = c = getch()) )
                ;
        }
    } else {
        if ( isdigit(c) ) /* continue to collect integer part */
            while ( isdigit(s[++i] = c = getch()) )
                ;
    }

    if ( c == '.' )   /* collect fraction part */
        while ( isdigit(s[++i] = c = getch()) )
            ;
    s[i] = '\0';
    if ( c != EOF ) /* we collected one char too many */
        ungetch(c); /* if not EOF, push it back for next call to getop */
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


