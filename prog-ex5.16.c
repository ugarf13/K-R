#include <stdio.h>
#include <string.h>

#define MAXLINES 5000  /* max # of lines to be sorted */

char  *lineptr[MAXLINES]; /*array of char pointers */

int  fold = 0;      /* 1 if sorting is case insensitive */

int   readlines (char *lineptr[], int nlines);
void  writelines (char *lineptr[], int nlines);

void  myqsort (void *lineptr[], int left, int right, 
             int (*comp)(void *, void *), int reverse);
int   numcmp (char *, char *);
int   charcmp (char *s1, char*s2);
int   dircmp (char *s1, char*s2);

/* program to sort input lines */
int main (int argc, char *argv[])
{
    int  c;
    int  nlines;        /* number of lines to be sort4ed */
    int  numeric = 0;   /* 1 if numeric sort */
    int  reverse = 1;   /* -1 if sorting in decreasing order */
    int  directory = 0; /* 1 if sorting by directory order */

    while ( --argc > 0 && (*++argv)[0] == '-' )
        while ( c = *++argv[0] ) 
            switch ( c ) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = -1;
                    break;
                case 'f':
                    fold = 1; /* defined global variable */
                    break;
                case 'd':
                    directory = 1;
                    break;
                default:
                    printf("error: illegal option\n");
                    printf("Usage: sort -rn\n");
                    return -1; /* end program */
        }

    if ( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        if ( numeric )
            myqsort((void **) lineptr, 0, nlines - 1, /* sort the lines that have been read */
              (int (*)(void *, void *)) numcmp, reverse);      
        else if ( directory) /* also takes care of fold */
            myqsort((void **) lineptr, 0, nlines - 1, /* sort the lines that have been read */
              (int (*)(void *, void *)) dircmp, reverse);      
        else if ( fold ) 
            myqsort((void **) lineptr, 0, nlines - 1, /* sort the lines that have been read */
              (int (*)(void *, void *)) charcmp, reverse);      
        else
            myqsort((void **) lineptr, 0, nlines - 1, /* sort the lines that have been read */
              (int (*)(void *, void *)) strcmp, reverse);      

        writelines(lineptr, nlines); /* display sorted lines */
        return 0; /* mission accomplished w/o errors */
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

/* ****************************************** */
/* read and write routines */

#include <ctype.h> /* for tolower() */

#define  MAXLEN 1000  /* max length of any input line */

int   mygetline (char *, int);
char  *alloc (int);

/* readlines: read input lines */
int  readlines (char *lineptr[], int maxlines)
{
    int   len, nlines;
    char  *p;  /* pointer to last line that was read */
    char  line[MAXLEN]; /* char array to store last line read */

    nlines = 0; /* keep track of how many lines have been read so far */
    while ( (len = mygetline(line, MAXLEN)) > 0 )
        if ( nlines >= maxlines || (p = alloc(len + 1)) == NULL ) 
            /* len + 1 because I won't to have space also for '\0' at the
             * end of each line */
            return -1;
        else {
            //line[len - 1] = '\0'; /* because line ends with '\n' */
            strcpy(p, line); /* copy line to pointer p */
            lineptr[nlines++] = p; /* store pointer to current line in lineptr */
            //printf("***%s\n", lineptr[nlines-1]);
        }
    return nlines;
}
            
/* writelines: write output lines */
void  writelines (char *lineptr[], int nlines)
{
    while ( nlines-- > 0 )
        printf("%s\n", *lineptr++); /* lineptr is also a pointer */
}

/* mygetline: get a line from input and store it; returns length of line */
int  mygetline (char *line, int maxlen)
{
    char  c;
    char  *bline = &line[0]; /* remember beginning of line */

    while ( maxlen-- > 0 && (c = getchar()) != EOF && c != '\n' ) {
        *line++ = c;
    }
    *line = '\0';
    //printf("***%s\n", bline);
    return line - bline; /* length of line */
}

/* **************************************** */
/* The way that multiple lines are stored is by creating a very long
 * array and then I store each new line inside this array. A pointer is
 * used signal where a specific line is located inside the array to access it
 * later on */
#define ALLOCSIZE 10000 /* size of available space */

static char  allocbuf[ALLOCSIZE];  /* storage for alloc */
static char  *allocp = allocbuf;   /* next free position */

char  *alloc (int n)   /* return pointer to n characters */
{
    if ( allocbuf + ALLOCSIZE - allocp >= n ) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else     /* not enough room */
        return 0;
}

void  afree (char *p)  /* free storatge pointed to by p */
{
    if ( p >= allocbuf && p < allocbuf + ALLOCSIZE )
        allocp = p;
}

/* ****************************************** */

/* myqsort: sort v[left],...,v[right] into ascending order */
void  myqsort (void *v[], int left, int right,
             int (*comp)(void *, void *), int reverse)
{
    int   i, last;
    void  swap (void *v[], int i, int j);

    if ( left >= right )
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for ( i = left + 1; i <= right; i++ )
        if ( reverse * (*comp)(v[i], v[left]) < 0 ) /* (*comp), pointer to comparison function */
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1, comp, reverse);
    myqsort(v, last + 1, right, comp, reverse);
}

/* swap: interchange v[i] and v[j] */
void  swap (void *v[], int i, int j)
{
    void  *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* ******************************************* */

#include <stdlib.h>
#include <ctype.h>

/* numcmp: compare s1 and s2 numerically */
int  numcmp (char *s1, char *s2)
{
    double  v1, v2;
    
    v1 = atof(s1);
    v2 = atof(s2);
    //printf("%s, %s, v1 < v2 = %i\n", s1, s2, v1 < v2);
    if ( v1 < v2 )
        return -1;
    else if ( v1 > v2 )
        return 1;
    else
        return 0;
}

/* charcmp: compare s1 and s2 lexicographically but case insensitive */
int  charcmp (char *s1, char*s2)
{
    for ( ; tolower(*s1) == tolower(*s2); s1++, s2++ )
        if ( *s1 == '\0' )
            return 0;
    return tolower(*s1) - tolower(*s2);
}

/* dircmp: compare s1 and s2 in directory order */
int  dircmp (char *s1, char *s2)
{
    int  isAllowedChar (char s);
    char  folded (char c);

    while ( *s1 && *s2 ) {
        for ( ; folded(*s1) == folded(*s2); s1++, s2++ ) {
            //printf("s1 = %c, s2 = %c\n", *s1, *s2);
            if ( *s1 == '\0' )
                return 0;
        }
        while ( !isAllowedChar(*s1) && *s1 ) { /* make sure it's not null */
            //printf("s1 = %c\n", *s1);
            s1++;
        }

        while ( !isAllowedChar(*s2) && *s2 ) {
            //printf("s2 = %c\n", *s2);
            s2++;
        }
        if ( folded(*s1) > folded(*s2) ) {
            //printf("s1 = %c, s2 = %c\n", *s1, *s2);
            return 1;
        } else if ( folded(*s1) < folded(*s2) ) {
            //printf("s1 = %c, s2 = %c\n", *s1, *s2);
            return -1;
        }
        /* else, *s1 = *s2, do nothing and move to next iteration */
    }

    /* at this point we reached the end of one of the two strings
     * and we have not returned yet, so compare what is left */
    if ( *s1 == '\0' ) {
        if ( *s2 == '\0' )
            return 0;
        else { 
            while ( !isAllowedChar(*s2) )
                s2++;
            if ( *s2 == '\0' )
                return 0;
            else
                return -1;
        }
    }
    if ( *s2 == '\0' ) {
        if ( *s1 == '\0' )
            return 0;
        else { 
            while ( !isAllowedChar(*s1) )
                s1++;
            if ( *s1 == '\0' )
                return 0;
            else
                return 1;
        }
    }
}


/* isAllowedChar: returns 1 if s is either a letter, a number, or a space */
int  isAllowedChar (char s)
{
    if ( isalnum(s) || s == ' ' )
        return 1;
    else 
        return 0;
}

/* folded: if fold = 1, convert char to lowercase, else leave it as is */
char  folded (char c)
{
    if ( fold && isalpha(c) )
        return tolower(c);
    else
        return c;
}









