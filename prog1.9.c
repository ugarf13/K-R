/* Program to print longest input line */

#include <stdio.h>

#define MAXLINE  1000 /* max char length of a line */

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

/* copyLine: copy content of a string 'from' to string 'to' */
void  copyLine ( char to[], char from[] )
{
    int  i;

    for ( i = 0; from[i] != '\0'; ++i )
        to[i] = from[i];
    to[i] = '\0';

    return;
}

int main (void)
{
    int   readLine ( char buffer[] , int maxline);
    void  copyLine ( char to[], char from[] );
    int   maxValue = 0;         /* current max length of strings inputted */
    int   len;                  /* length of current string */
    char  buffer[MAXLINE];      /* char string to store current line */
    char  longestLine[MAXLINE]; /* char string to store longest running line */

    while ( 1 )
    {
        len = readLine(buffer, MAXLINE);
        if ( len == 0 )
            break;
        else if ( len > maxValue ) /* current line is the longest */
        {
            maxValue = len; /* update the length of longest line so far */
            copyLine(longestLine, buffer); /* store the current longest line */
        }                
    }

    if ( maxValue > 0 )
        printf("\nThe longest line is:\n\n");
        printf("%s\n", longestLine);

    return 0;
}





