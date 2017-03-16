#include <stdio.h>
#include <string.h> 
#include <ctype.h>
#include <stddef.h>

struct key {
    char  *word;
    int   count;
};

struct key  keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    /* ... */
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 },
};

#define NKEYS  ((sizeof keytab) / (sizeof keytab[0]))
#define MAXWORD 100

int  getword (char *, int);
struct key *binsearch (char *, struct key *, int);

/* count C keywords */
int  main (void)
{
    char        word[MAXWORD];
    struct key  *p;

    while ( getword(word, MAXWORD) != EOF ) {
        if ( isalpha(word[0]) )
            if ( (p = binsearch(word, keytab, NKEYS)) != NULL )
                p->count++;
    }
    for ( p = keytab; p < keytab + NKEYS; p++ )
        if ( p->count > 0 )
            printf("%4d %s\n", p->count, p->word);
    
    return 0;
}

struct key  *binsearch (char *word, struct key *keytab, int n)
{
    struct key  *low  = &keytab[0];
    struct key  *high = &keytab[n];
    struct key  *mid;

    while ( low <= high ) {
        mid = low + (high - low) / 2; /* some of pointers is illegal, but difference is not */
        if ( strcmp(word, mid->word) < 0 )
            high = mid - 1;
        else if ( strcmp(word, mid->word) > 0 )
            low = mid + 1;
        else   /* word found */
            return mid;
    }
    return NULL; /* word not found */
}


/* getword: get a new word */
int  getword (char *word, int lim)
{
    int   c;
    char *w = word;
    int   getch (void);
    void  ungetch (int);

    while ( isspace(c = getch()) )
        ;
    if ( c != EOF )
        *w++ = c;
    if ( !isalpha(c) ) { /* end it here */
        *w = '\0';
        return c;
    }

    while ( --lim && isalnum( c = getch() ) )
        *w++ = c;
    ungetch(c);
    *w = '\0';

    return word[0];
}


/* ********************************************* */

#define BUFSIZE 1000

char  buf[BUFSIZE];  /* buffer */
char  *bufp = buf;   /* next free position in buffer */
char *p = buf;       /* remember beginning of buffer */

int  getch (void)
{
    return (bufp - p > 0) ? *--bufp : getchar();
}


void ungetch (int c)
{
    if ( bufp > p + BUFSIZE )
        printf("ungetch: no more space on the buffer\n");
    else
        *bufp++ = c;
}

