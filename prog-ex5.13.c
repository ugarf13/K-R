#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* for atoi() */
#include <ctype.h>   /* for isdigit() */

#define  MAXLINES 5000
#define  DEFLINES 10

char  *lineptr[MAXLINES]; /*array of char pointers */

int   readlines (char *lineptr[], int nlines);
void  writelines (char *lineptr[], int nlines, int n);


/* find: print lines that match pattern from 1st arg */
int main (int argc, char *argv[])
{
    int   n = DEFLINES; /* number of lines to print, default = 10 */
    int   c, number = 0;
    int   nlines;    /* number of lines received from input */

    while ( --argc > 0 && (*++argv)[0] == '-' )
        while ( (c = *++(*argv)) ) /* walk through the argument string */
            switch (c) {
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("mytail: illegal option %c\n", c);
                    return -1; /* error */
            }
    if ( number ) 
        n = atoi(*argv); /* if next arg  not a number, atoi(s) returns 0 */
    if ( n == 0 ) {
        printf("error: too few arguments or 0 lines requested\n");
        return -1;
    }

    if ( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        writelines(lineptr, nlines, n); /* display lines */
        return 0; /* mission accomplished w/o errors */
    } else {
        printf("Error: input too big to handle\n");
        return 1;
    }
}


/* ******************************************************* */
/* read and write routines */

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
void  writelines (char *lineptr[], int nlines, int n)
{
    int   start = nlines - n;

    if ( start >= 0 ) {        /* enough lines */
        while ( start-- > 0 )
            lineptr++;
        while ( n-- > 0 ) 
            printf("%s\n", *lineptr++); /* else just use lineptr[start++] */
    } else {  /* not enough lines, then print all of them */
        while ( nlines-- > 0 )
            printf("%s\n", *lineptr++); /* lineptr is also a pointer */
    }
}

/* mygetline: get a line from input and store it; returns length of line */
int  mygetline (char *line, int maxlen)
{
    char  c;
    char  *bline = &line[0]; /* remember beginning of line */

    while ( maxlen-- > 0 && (c = getchar()) != EOF && c != '\n' )
        *line++ = c;
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

/* free storage pointed to by p */
/* void  afree (char *p)  
{
    if ( p >= allocbuf && p < allocbuf + ALLOCSIZE )
        allocp = p;
} */


