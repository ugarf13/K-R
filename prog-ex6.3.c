#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define  MAXWORD 100
#define MAXWORDS 1000

struct tnode {           /* definition of a tree node: */
    char   *word;           /* pointer to text */
    int    linenum[30];     /* list of line numbers on which word occurs */ 
    int    n;               /* number of line numbers inserted */
    struct tnode  *left;    /* pointer to left leaf */
    struct tnode  *right;   /* pointer to right leaf */
};

struct tnode  *addtree (struct tnode *, char *);
void          treeprint (struct tnode *);
int           getword (char *, int);
int           getch (void);
void          ungetch (int);
int           isOkWord (char *);

//int  nwords = 0; /* counter of number of unique words */
int  nline  = 0; /* number of current line */


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
    treeprint(root);
    
    return 0;
}

/* getword: get a new word */
int  getword (char *word, int lim)
{
    int   c;
    char  *w = word;
    int   checkNotAlpha (char *s, char c); /* could be string, comment, prepro, etc. */

    while ( isspace(c = getch()) ) {
        if ( c == '\n' ) /* need to differentiatie, else it would skip '\n' */
            break;
        else
            ;
    }
    if ( c != EOF ) {
        if ( !isalpha(c) ) { /* end it here */
            checkNotAlpha(w, c);
            //printf("c= %c\n", c);
            if ( c == '\n' )
                nline++;
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
       (p->linenum)[0] = nline;  /* current line on which word was found */
       p->n = 1;
       p->left = NULL;
       p->right = NULL;
   } else if ( (cond = strcmp(w, p->word)) == 0 ) { 
       //printf("nline: %d\n", p->linenum[p->n]);
       if ( nline > (p->linenum)[(p->n)-1] ) { /* if current line, is > than last line found */
           //printf("increment nline\n");
           (p->linenum)[p->n] = nline;  /* add new line where word was found */
           p->n += 1;
       }
   } else if ( cond > 0 )  /* w not found, but greater then p->word, move to right node */
       p->right = addtree(p->right, w);
   else  /* move to left node */
       p->left = addtree(p->left, w);
   return p;
}

/* ********************************** */

/* treeprint: print each unique word and list of line numbers on which it cocurs */
void  treeprint (struct tnode *p)
{
    int  i;

    if ( p != NULL ) {
        treeprint(p->left);

        printf("%s: ", p->word);
        for ( i = 0; i < p->n; ++i  )
            printf("%d, ", (p->linenum)[i]);
        printf("\b\b \n");  /* \b simply moves the cursor back, so the space is used to
                                 erase the trailing comma */

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

