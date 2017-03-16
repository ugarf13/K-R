/* reverse Polish calculator */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */

int     getop (char s[]);
void    push  (double f);
double  pop   (void);
    

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
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("Error: Unknown command.\n");
        }
    }

    return 0;
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
    static int  lastc = 0;

    if ( lastc == 0 ) /* empty buffer */
        c = getchar();
    else {
        c = lastc; /* get char from buffer */
        lastc = 0; /* clean up the buffer */
    }
     
    while ( (s[0] = c ) == ' ' || c == '\t' )
        c = getchar(); /* get new char until not white space */
    s[1] = '\0';
    i = 0;
    if ( !isdigit(c) && c != '.' && c != '-')
        return c;    /* not a number */

    if ( c == '-' ) {
        if ( isdigit(c = getchar()) || c == '.' )
            s[++i] = c; /* it's negative number */
        else {          /* it's a minus operator */
            if ( c != EOF )
                lastc = c;
        return '-';
        }
    }
    
    if ( isdigit(c) ) /* collect integer part */
        while ( isdigit(s[++i] = c = getchar()) )
            ;
    if ( c == '.' )   /* collect fraction part */
        while ( isdigit(s[++i] = c = getchar()) )
            ;
    s[i] = '\0';
    if ( c != EOF )
        lastc = c;
    return NUMBER;
}



