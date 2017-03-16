#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define  MAXWORD 100

struct tnode {           /* definition of a tree node: */
    char   *word;           /* pointer to text */
    int    count;           /* counter of # of occurrences of word */ 
    struct tnode  *left;    /* pointer to left leaf */
    struct tnode  *right;   /* pointer to right leaf */
};

struct tnode  *addtree (struct tnode *, char *);
void          treeprint (struct tnode *);
int           getword (char *, int);


int  main (void)
{
    struct tnode  *root;
    char          word[MAXWORD];

    root = NULL; /* init root to NULL pointer */
    while ( getword(word, MAXWORD) != EOF )
        if ( isalpha(word[0]) )
            root = addtree(root, word); /* find word in tree, or add it as leaf if new */
    treeprint(root);
    return 0;
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

/* ************************************** */

struct tnode  *talloc (void);
char *mystrdup (char *);

/* addtree: add a node with w, at or below p */
struct tnode  *addtree (struct tnode *p, char *w)
{
   int cond;

   if ( p == NULL ) {    /* w is a new word, so create new leaf */
       p = talloc();     /* make a new node */
       p->word = mystrdup(w);
       p->count = 1;
       p->left = NULL;
       p->right = NULL;
   } else if ( (cond = strcmp(w, p->word)) == 0 )
       p->count++;  /* w = p->word, so increase counter */
   else if ( cond > 0 )  /* w not found, but greater then p->word, move to right node */
       p->right = addtree(p->right, w);
   else  /* move to left node */
       p->left = addtree(p->left, w);
   return p;
}


/* treeprint: print tree p in order */
void  treeprint (struct tnode *p)
{
    if ( p != NULL ) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}


#include <stdlib.h> /* for malloc */
/* talloc: make a tnode */
struct tnode  *talloc (void)
{
    return  (struct tnode *) malloc(sizeof(struct tnode));
}


/* mystrdup: make a duplicate of s */
char  *mystrdup (char *s)
{
    char  *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if ( p != NULL ) /* there is enough space */
        strcpy(p, s);
    return p;
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

