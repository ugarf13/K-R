#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE  101  /* size of hash table */

struct nlist {             /* table entry: */
    struct nlist  *next;        /* next entry in chain */
    char          *name;        /* defined name */
    char          *defn;        /*replacement text */
};

static struct nlist  *hashtab[HASHSIZE];  /* hash table */

unsigned      hash (char *);
struct nlist  *lookup (char *);
char          *mystrdup (char *);
struct nlist  *install (char *, char *);
void          *undef (char *);

int  main (void)
{
    char  *s  = "hello";
    char  *s1 = "helow";
    struct nlist  *np;

    np = install(s, "1");
    printf("%s = %s\n", np->name, np->defn); 
    np = install(s1, "0");
    printf("%s = %s\n", np->name, np->defn); 
    //printf("hashval = %u\n", hash(s1));


    undef(s);
    np = lookup(s);
    printf("%s = %s\n", s, np == NULL ? s : np->defn);

    return 0;
}


/* hash: form hash value for string s */
unsigned  hash (char *s)
{
    unsigned  hashval;

    for ( hashval = 0; *s != '\0'; s++ )
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in the hashtab */
struct nlist  *lookup (char *s)
{
    unsigned      hashval;
    struct nlist  *np;

    hashval = hash(s);
    for ( np = hashtab[hashval]; np != NULL; np = np->next )
        if ( strcmp(np-> name, s) == 0 )
            return np;
    return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist  *install (char *name, char *defn)
{ 
    struct nlist  *np;
    unsigned      hashval;

    if ( (np = lookup(name)) == NULL ) {   /* not found */
        np = (struct nlist *) malloc(sizeof(struct nlist));
        if ( np == NULL || (np->name = mystrdup(name)) == NULL )
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval]; /* put np at the top of the block */
        hashtab[hashval] = np;
    } else          /* already there */
        free((void *) np->defn);    /* free previous defn */
    if ( (np->defn = strdup(defn)) == NULL )
        return NULL;
    return np;
}


/* mystrdup: copy s */
char  *mystrdup (char *s)
{
    char  *t;

    t = (char *) malloc(sizeof(s));
    strcpy(t, s);

    return t;
}


/* undef: remove a name and definition associated with s from hashtable */
void  *undef (char *s)
{
    struct nlist  *np;
    struct nlist  *prev;

    if ( lookup(s) != NULL ) {
        for ( np = hashtab[hash(s)], prev = NULL; np != NULL; ) {
            if ( strcmp(s, np->name) == 0 )
                break;
            prev = np;
            np = np->next;
        }
        if ( prev == NULL )
            hashtab[hash(s)] = np->next;
        else 
            prev->next = np->next; /* point prev to element after np */
        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);     /* free memory allocated to np */
    } 
    return NULL;
}






