#include <stdio.h>
#include <string.h>

#define MAXLINES 5000  /* max # of lines to be sorted */
#define BUFFSIZE 1000  /* size of storage buffer */

char  *lineptr[MAXLINES]; /* array of char pointers */

int   readlines (char *lineptr[], char buffer[], int nlines);
void  writelines (char *lineptr[], int nlines);

void  qsort (char *lineptr[], int left, int right);

/* program to sort input lines */
int main (void)
{
    int  nlines;    /* number of lines to be sort4ed */
    char  buffer[BUFFSIZE];   /* array to store input lines */

    if ( (nlines = readlines(lineptr, buffer, MAXLINES)) >= 0 ) {
        qsort(lineptr, 0, nlines - 1); /* sort the lines that have been read */
        writelines(lineptr, nlines); /* display sorted lines */
        return 0; /* mission accomplished w/o errors */
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

/* ****************************************** */
/* read and write routines */

#define  MAXLEN 1000  /* max length of any input line */

int   mygetline (char *, int);
char  *alloc (int);

/* readlines: read input lines */
int  readlines (char *lineptr[], char buffer[], int maxlines)
{
    int   len, nlines;
    char  *p = buffer;  /* pointer to beginning in buffer of last line that was read */
    char  *endbuff = buffer + BUFFSIZE; /* end of buffer */
    char  line[MAXLEN]; /* char array to store last line read */

    nlines = 0; /* keep track of how many lines have been read so far */
    while ( (len = mygetline(line, MAXLEN)) > 0 )
        if ( nlines >= maxlines || p + (len + 1) >= endbuff ) 
            /* len + 1 because I won't to have space also for '\0' at the
             * end of each line */
            return -1;
        else {
            strcpy(p, line); /* copy line to pointer p */
            *lineptr++ = p; /* store pointer to current line in lineptr */
            ++nlines;
            p += len + 1; /* update index of next free position in buffer */
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

    while ( maxlen-- > 0 && (c = getchar()) != EOF && c != '\n' )
        *line++ = c;
    *line = '\0';
    //printf("***%s\n", bline);
    return line - bline; /* length of line */
}


/* ****************************************** */

/* qsort: sort v[left],...,v[right] into ascending order */
void  qsort (char *v[], int left, int right)
{
    int   i, last;
    void  swap (char *v[], int i, int j);

    if ( left >= right )
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for ( i = left + 1; i <= right; i++ )
        if ( strcmp(v[i], v[left]) < 0 )
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void  swap (char *v[], int i, int j)
{
    char  *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

















