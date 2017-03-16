#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define  MAXWORD 100
#define MAXWORDS 1000

struct tnode {           /* definition of a tree node: */
    char   *word;           /* pointer to text */
    int    count;           /* number of occurrences */ 
    struct tnode  *left;    /* pointer to left leaf */
    struct tnode  *right;   /* pointer to right leaf */
};

struct tnode  *addtree (struct tnode *, char *);
void          sortnodes (struct tnode *[], int, int);
void          treeprint (struct tnode *[], int);
int           getword (char *, int);
int           getch (void);
void          ungetch (int);
int           isOkWord (char *);

int  nwords = 0; /* counter of number of unique words */
struct tnode  *ptrnodes[MAXWORDS]; /* array of pointers to nodes */

int  main (void)
{
    struct tnode  *root;
    char          word[MAXWORD];

    root = NULL; /* init root to NULL pointer */
    while ( getword(word, MAXWORD) != EOF ) {
        //printf("(noise word? %s)\n", !isOkWord(word) ? "Yes" : "No");
        if ( isalpha(word[0]) && isOkWord(word) ) 
            root = addtree(root, word); /* find word in tree, or add it as leaf if new */
    }
    
    sortnodes(ptrnodes, 0, nwords - 1);
    treeprint(ptrnodes, nwords);

    return 0;
}

/* getword: get a new word */
int  getword (char *word, int lim)
{
    int   c;
    char  *w = word;
    int   checkNotAlpha (char *s, char c); /* could be string, comment, prepro, etc. */

    while ( isspace(c = getch()) ) {
        ;
    }
    if ( c != EOF ) {
        if ( !isalpha(c) ) { /* end it here */
            checkNotAlpha(w, c);
            //printf("c= %c\n", c);
            return word[0];
        }

        *w++ = c; /* c is alpha so put it in w */
        while ( --lim && isalnum( c = getch() ) )
            *w++ = c;
        ungetch(c);
    } else  /* c == EOF */
        *w++ = c;
    *w = '\0';

    return word[0];
}

int  checkNotAlpha (char *s, char c)
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
                *s++ = d;
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
    } else { 
        *s++ = c;
    }
    *s = '\0';
    //printf("%s\n", &s[0]);
    return found;
}

/* isOkWord: return 1 if word is not in the list of noise words, 0 otherwise */
int  isOkWord (char *s)
{
    char  *noisewords[] = { "a", "an", "and", "are", "in", "is", "of",
                        "or", "that", "the", "this", "to" };
    int   low = 0;
    int   high = sizeof(noisewords) / sizeof(noisewords[0]) - 1;
    int   mid;
    int   cond;

    while ( low <= high ) {
        mid = low + (high - low) / 2;
        if ( (cond = strcmp(s, noisewords[mid])) < 0 )
            high = mid - 1;
        else if ( cond > 0 )
            low = mid + 1;
        else
            return 0; /* s is a noise word */
    }
    return 1; /* s is not a noise word */
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
       p->word = mystrdup(w); /* need to copy the word, if we simply point, w will change */
       p->count = 1;     /* current line on which word was found */
       p->left = NULL;
       p->right = NULL;
       ptrnodes[nwords++] = p; /* add pointer to list of pointers to nodes */
   } else if ( (cond = strcmp(w, p->word)) == 0 ) { 
           p->count++;
   } else if ( cond > 0 )  /* w not found, but greater then p->word, move to right node */
       p->right = addtree(p->right, w);
   else  /* move to left node */
       p->left = addtree(p->left, w);
   return p;
}

/* ********************************** */

/* treeprint: print each unique word and list of line numbers on which it cocurs */
void  treeprint (struct tnode *ptrnodes[], int nwords)
{
    int i;

    for ( i = 0; i < nwords; ++i )
        printf("%4d %s\n", ptrnodes[i]->count, ptrnodes[i]->word);
}

/* sortnodes: sorts pointers to nodes inside list in decreasing order of occurrence of
 * their word, based on qsort */
void  sortnodes (struct tnode *ptrnodes[], int left, int right)
{
    int   i, last;
    void  swap (struct tnode *ptrnodes[], int i, int j);
    
    if ( left >= right )
        return;
    swap(ptrnodes, left, (left + right) / 2);
    last = left;
    for ( i = left + 1; i <= right; i++ ) {
        if ( ptrnodes[i]->count > ptrnodes[left]->count )
            swap(ptrnodes, ++last, i);
        else if ( ptrnodes[i]->count == ptrnodes[left]->count )
            if ( strcmp(ptrnodes[i]->word, ptrnodes[left]->word) < 0 )
                swap(ptrnodes, ++last, i);
    }
    swap(ptrnodes, left, last);
    sortnodes(ptrnodes, left, last - 1);
    sortnodes(ptrnodes, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void  swap (struct tnode *v[], int i, int j)
{
    struct tnode *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

