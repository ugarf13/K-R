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
int  binsearch (char *, struct key *, int);

/* count C keywords */
int  main (void)
{
    int   i, n, w;
    char  word[MAXWORD];

    while ( (w = getword(word, MAXWORD)) != EOF ) {
        if ( isalpha(w) )
            if ( (n = binsearch(word, keytab, NKEYS)) >= 0 )
                keytab[n].count++;
    }
    for ( i = 0; i < NKEYS; ++i )
        if ( keytab[i].count > 0 )
            printf("%4d %s\n", keytab[i].count, keytab[i].word);
    
    return 0;
}

int  binsearch (char *word, struct key *keytab, int n)
{
    int  low, mid, high;

    low = 0;
    high = n - 1;

    while ( low <= high ) {
        mid = (low + high) / 2;
        if ( strcmp(word, keytab[mid].word) < 0 )
            high = mid - 1;
        else if ( strcmp(word, keytab[mid].word) > 0 )
            low = mid + 1;
        else   /* word found */
            return mid;
    }
    return -1; /* word not found */
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

