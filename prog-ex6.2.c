#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define  MAXWORD 100
#define MAXWORDS 1000

struct tnode {           /* definition of a tree node: */
    char   *word;           /* pointer to text */
    int    count;           /* counter of # of occurrences of word */ 
    struct tnode  *left;    /* pointer to left leaf */
    struct tnode  *right;   /* pointer to right leaf */
};

struct tnode  *addtree (struct tnode *, char *);
void          treeToList (struct tnode *);
int           getword (char *, int);
void          printGroupN (char * [], int n);
int           getch (void);
void          ungetch (int);

int  nwords = 0; /* counter of number of unique words */
char *lineptr[MAXWORDS]; /* array of pointers to unique words, ordered lexic */


int  main (int argc, char *argv[])
{
    struct tnode  *root;
    char          word[MAXWORD];
    int           n;  /* number of characters that need to be matched */

    if ( argc == 1 )
        n = 0;
    else if ( argc == 2 && (*++argv)[0] == '-')
        n = atoi(argv[0] + 1); /* argv already pointing to second argument, next point to 2nd char */
    else {
        printf("Usage: prog-ex6.2 [-n]");
        return -1;
    }

    root = NULL; /* init root to NULL pointer */
    while ( getword(word, MAXWORD) != EOF )
        if ( isalpha(word[0]) && strlen(word) >= n)
            root = addtree(root, word); /* find word in tree, or add it as leaf if new */
    treeToList(root);
    printGroupN(lineptr, n);
    
    return 0;
}

/* getword: get a new word */
int  getword (char *word, int lim)
{
    int   c;
    char  *w = word;
    int   checkNotToken (char *s, char c);

    while ( isspace(c = getch()) )
        ;
    if ( c != EOF )
        ;
    if ( !isalpha(c) ) { /* end it here */
        checkNotToken(w, c);
        //printf("%s\n", word);
        return word[0];
    }

    *w++ = c; /* c is alpha so put it in w */
    while ( --lim && isalnum( c = getch() ) )
        *w++ = c;
    ungetch(c);
    *w = '\0';

    return (int) word[0];
}

int  checkNotToken (char *s, char c)
{
    int  d;
    int  found = 0; /* flag to indicate that token was found */

    if ( c == '#' ) { /* move to next char */
        while ( isalnum(c = getch()) ) {
            *s++ = c;
        }
        ungetch(c);
        found = 1;
    } else if ( c == '/' ) {
        if ( (d = getch()) == '*' ) {  /* it's a comment */
            while ( (c = getch()) != '*' && c != EOF ) 
                ;
            if ( c == '*' && (d = getch()) == '/'  ) /* end of comment */
                *s++ = c;
            else
                printf("checkNotToken: comment is missing closing brackets\n");
                exit(1);
        } else {
            *s++ = c;
            ungetch(d);
            while ( isalnum(c = getch()) ) {
                *s++ = c;
            }
            ungetch(c);
        }
    } else if ( c == '\'' || c == '"' ) { /* it's a string */
        if ( c == '\'' )
            while ( (d = getch()) != c )
                ;
        else 
            while ( (d = getch()) != c )
                ;
        *s++ = d;    
    } else 
        *s++ = c;
    *s = '\0';
    //printf("%s\n", &s[0]);
    return found;
}


/* printGroupN: print each group of variable names that are identical in the
 * first n characters, but different somewhere thereafter 
 * NB: current version does not prints single words, that is, there must be at
 * least 2 words in a group for its words to be printed out */
void  printGroupN (char *lineptr[], int n)
{
    int  i, j = 0;
    char *prev;
    char *groupptr[MAXWORDS];
    char *end_lineptr = lineptr + nwords;
    
    for ( ; lineptr < end_lineptr; lineptr++ ) {
        if ( j > 0 ) { /* groupptr is not empty */
            prev = groupptr[j - 1]; /* previous word */
            if ( strncmp(prev, *lineptr, n) == 0 ) 
                groupptr[j++] = *lineptr;
            else if ( j > 1 ){  /* empty groupptr if at least 2 words are in it */
                for ( i = 0; i < j; i++ )
                    printf("%s\n", groupptr[i]);
                j = 0; /* restart groupptr */
                groupptr[j++] = *lineptr;
            }
        } else 
            groupptr[j++] = *lineptr;
    }

    if ( j > 1 ) 
        for ( i = 0; i < j; i++ )
            printf("%s\n", groupptr[i]);
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

/* ********************************** */

/* treeToList: make a list of pointers to words in lexicographic order */
void  treeToList (struct tnode *p)
{
    if ( p != NULL ) {
        treeToList(p->left);
        
        lineptr[nwords++] = p->word;

        treeToList(p->right);
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

