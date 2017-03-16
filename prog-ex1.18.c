/* Program to remove trailing blanks and tabs from each line of input, and to
 * delete entirely blank lines */

#include <stdio.h>

#define MAXLINE  1000 /* max char length of a line */

/* readLine: store line from input into 'buffer', returns length of line */
int  readLine ( char buffer[], int maxline )
{
    int  c;      /* char used to store input */
    int  i = 0;  /* index variable */

    while ( ( c = getchar() ) != '\n' && c != EOF && i < maxline - 1 )
    {
        buffer[i] = c;
        ++i;
    }
    
    buffer[i] = '\0';

    return i; /* returns length of line, excluding null char */
}

/* removeTrailing: remove trailing blanks and tabs, return length of cleaned
 * line */
int  removeTrailing ( char buffer[] )
{
    int  i = 0;  /* index variable */

    while ( buffer[i] != '\0' )
        ++i;
    
    --i; /* index of last char before termination char */
    /* loop backwards until you find non whitespace or beginning of string */
    while ( i >= 0 && (buffer[i] == ' ' || buffer[i] == '\t') )
        --i;

    if ( i >= 0 ) /* line is nonblank */
    {
        ++i;
        buffer[i] = '\0'; /* i is the index of last non white space char */
    }

    return i; /* returns length of line, excluding null char */
}

int main (void)
{
    int   removeTrailing ( char buffer[] );
    int   readLine ( char buffer[] , int maxline);
    char  buffer[MAXLINE];      /* char string to store current line */

    while ( readLine(buffer, MAXLINE) > 0 )
    {
        if ( removeTrailing(buffer) > 0 )
            printf("%s\n", buffer);
    }

    return 0;
}





