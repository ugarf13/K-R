/* reverse Polish calculator */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <string.h>
#include <ctype.h>

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */
#define BUFSIZE  100  /* store comman-line args in reverse order */

char  buf[BUFSIZE];  /* buffer for ungetch */
int   bufp = 0;      /* next free position in buf */

int     getop (char s[]);
void    push  (double f);
double  pop   (void);
void    ungetch (int);
void    reverse (char *s);

int  main (int argc, char *argv[])
{
    int     type;
    double  op2;
    char    s[MAXOP];
    char    *arg;

    if ( argc == 1 ) {
        printf("Error: need arguments\n");
        return -1;
    }

    while ( --argc > 0 ) {
        arg = *++argv;
        //printf("%s\n", arg);
        while ( *arg ) {
            //printf("%c\n", *arg);
            ungetch(*arg++); //buf[bufp++] = *arg++;
        }
        ungetch(' '); //buf[bufp++] = ' ';
    }
    //for ( int i = 0; i < bufp; ++i )
    //    printf("buf[%i] = %c\n", i, buf[i]);
    reverse(buf);    
    //for ( int i = 0; i < bufp; ++i )
    //    printf("buf[%i] = %c\n", i, buf[i]);

    while ( (type = getop(s)) != EOF ) {
        //printf("%s\n", s);
        //printf("%c\n", type);
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
            default:
                printf("Error: Unknown command.\n");
                argc = 1;
                break;
        }
    }

    printf("result = %.8g\n", pop());
    return 0;
}

/* reverse: reverse string s */
void  reverse (char *s)
{
    char  temp;
    char  *end = s + (strlen(s) - 1); /* pointer to last char in s */  
    
    for ( ; s < end ; s++, end-- ) {
        temp = *s;
        *s = *end;
        *end = temp;
    }
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

/* getop: get next operator or numeric operand */
int  getop (char s[])
{
    int  i, c;

    while ( (s[0] = c = getch()) == ' ' || c == '\t' )
        ;
    s[1] = '\0';
    i = 0;
    if ( !isdigit(c) && c != '.' && c != '-')
        return c;    /* not a number */

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


int  getch (void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : EOF;
}


void  ungetch (int c) /* push character back on input */
{
    if ( bufp >= BUFSIZE )
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}


