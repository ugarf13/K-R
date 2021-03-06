#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void  dcl (void);
void  dirdcl (void);
void  errormsg (char *);

int   gettoken (void);
int   tokentype;            /* type of last token */
int   prevtoken = NO;
char  token[MAXTOKEN];      /* last token string */
char  name[MAXTOKEN];       /* identifier name */
char  datatype[MAXTOKEN];   /* data type = char, int, etc. */
char  out[1000];            /* output string */

int  main (void)  /* convert declaration to words */
{
    while ( gettoken() != EOF ) {  /* 1st token on line */
        strcpy(datatype, token);   /* is the datatype */
        out[0] = '\0';
        dcl();        /* parse rest of line */
        if ( tokentype != '\n' )
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}


/* gettoken: return next token */
int gettoken (void)
{
    int   c, getch (void);
    void  ungetch (int);
    char  *p = token;

    if ( prevtoken == YES ) {
        prevtoken = NO;
        return tokentype;
    }

    while ( (c = getch()) == ' ' || c == '\t' )
        ;
    if ( c == '(' ) {
        if ( (c = getch()) == ')' ) {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if ( c == '[' ) {
        for ( *p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if ( isalpha(c) ) {
        for ( *p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else 
        return tokentype = c;
}

/* dcl: parse a declarator */
void  dcl (void)
{
    int  ns;

    for ( ns = 0; gettoken() == '*'; )   /* count *'s */
        ns++;
    dirdcl();
    while ( ns-- > 0 )
        strcat(out, " pointer to");
}


/* dirdcl: parse a direct declarator */
void  dirdcl (void)
{
    int  type;
    
    if ( tokentype == '(' ) {   /* ( dcl ) */
        dcl();
        if ( tokentype != ')' )
            errormsg("error: missing ) \n");
    } else if ( tokentype == NAME )     /* variable name */
        strcpy(name, token);
    else
        errormsg("error: expected name or (dcl)\n");
    while ( (type = gettoken()) == PARENS || type == BRACKETS )
        if ( type == PARENS )
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}


/* errormsg: print error message and indicate available token */
void  errormsg (char *msg)
{
    printf("%s", msg);
    prevtoken = YES;
}


/* *************************************************** */

#define BUFSIZE 100  /* size of char buffer */

char  buf[BUFSIZE];  /* buffer to store chars */
char  *bufp = buf;   /* pointer to next free position inside buf */
char  *bbuf = buf;   /* remember beginning of buf */

int  getch (void)
{
    return (bufp - bbuf > 0) ? *--bufp : getchar();
}

void  ungetch (int c)
{
    if ( bufp > bbuf + BUFSIZE )
        printf("ungetch: not enough space inside the buffer\n");
    else
        *bufp++ = c;
}

