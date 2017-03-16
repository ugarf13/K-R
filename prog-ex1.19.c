/* Program to print all input lines that are longer than 80 characters */

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

/* reverseLine: reverses the characters in a string and store it in 'result' */
void  reverseLine ( char result[], char s[] )
{
    int  i = 0, j;  /* indeces used for looping */
    int  len = 0; /* length of s */

    for ( i = 0; s[i] != '\0'; ++i ) /* find end of string, excluding null char */
        ++len;
    
    for ( i = len - 1, j = 0; i >= 0; --i, ++j ) /* loop from end of s backwards */
        result[j] = s[i];
    
    result[j] = '\0';    
    
    return;
}


int main (void)
{
    int   readLine ( char buffer[] , int maxline);
    void  reverseLine ( char result[], char s[] );
    int   len;                  /* length of current string */
    char  buffer[MAXLINE];      /* char string to store current line */
    char  result[MAXLINE];

    while ( 1 )
    {
        len = readLine(buffer, MAXLINE);
        if ( len == 0 )
            break;
        else 
        {
            reverseLine(result, buffer);
            printf("%s\n", result);
        }                
    }

    return 0;
}





