/* Program to print all input lines that are longer than 80 characters */

#include <stdio.h>

#define MAXLINE  1000 /* max char length of a line */
#define MINPRINT 80   /* min length of line to be printed */

/* readLine: store line from input into 'buffer', returns length of line */
int  readLine ( char buffer[], int maxline )
{
    int  c;
    int  i = 0;

    while ( ( c = getchar() ) != '\n' && c != EOF && i < maxline - 1 )
    {
        buffer[i] = c;
        ++i;
    }

    buffer[i] = '\0'; /* replace \n with null char */

    return i; /* returns length of line, excluding null char */
}

int main (void)
{
    int   readLine ( char buffer[] , int maxline);
    int   len;                  /* length of current string */
    char  buffer[MAXLINE];      /* char string to store current line */

    while ( 1 )
    {
        len = readLine(buffer, MAXLINE);
        if ( len == 0 )
            break;
        else if ( len > MINPRINT ) /* current line is the longest */
        {
            printf("%s\n", buffer);
        }                
    }

    return 0;
}





