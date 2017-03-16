/* reverse Polish calculator */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <math.h>

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */

int     getop (char s[]);
void    push  (double f);
double  pop   (void);
void    print_top_stack (void);
void    duplicate (void);    
void    swap (void);
void    clear (void);

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
                if ( op2 != 0.0 )
                    push(fmod(pop(), op2));
                else
                    printf("Error: Zero division.\n");
                break;
            case 'p':
                print_top_stack();
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
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

/* print_top_stack: print top element of the stack without popping it */
void  print_top_stack(void) 
{
    if ( sp > 0 )
        printf("\t%g\n", val[sp - 1]);
    else
        printf("print_top_stock: No elements on the stack to print");
}

/* duplicate: duplicate top element of the stack */
void  duplicate (void)
{
    double temp;

    if ( sp > 0 && sp < MAXVAL ) {
        temp = val[sp - 1];
        val[sp++] = temp;
    } else 
        printf("duplicate: Stack empty.\n");
}

/* swap: swap top two elements of the stack */
void  swap (void)
{
   double temp;

   if ( sp - 2 > 0 ) {
       temp = val[sp - 1];
       val[sp - 1] = val[sp - 2];
       val[sp - 2] = temp;
   } else
        printf("swap: Not enough element on the stack to swap.\n");
}


/* clear: clears the stack */
void  clear (void)
{
    sp = 0;
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
    if ( !isdigit(c) && c != '.' && c != '-')
        return c;    /* not a number */

    if ( c == '-' ) {
        if ( isdigit(c = getchar()) || c == '.' )
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


