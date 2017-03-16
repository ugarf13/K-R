/* Program to remove trailing blanks and tabs from each line of input, and to
 * delete entirely blank lines */

#include <stdio.h>

#define MAXLINE  1000 /* max char length of a line */
#define TABSPACE 4    /* number of tab stops */

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

/* detab: replace tabs with equal number of spaces */
void  detab ( char  result[], char  buffer[] )
{
    int  i = 0, j = 0, k;  /* index variables */

    while ( buffer[i] != '\0' )
    {
        if ( buffer[i] == '\t' )
        {
            for ( k = 0; k < TABSPACE - 1; ++k)
                result[j + k] = ' ';
            j = j + k;
        }
        else
        {
            result[j] = buffer[i];
            ++j;
        }
        ++i;
    }

    result[j] = '\0';
    
    printf("string length with tabs = %i\n", i);
    printf("string length without tabs = %i\n", j);

    return;
}

int main (void)
{
    void  detab ( char  result[], char  buffer[] );
    int   readLine ( char buffer[] , int maxline);
    char  buffer[MAXLINE];  /* char string to store current line */
    char  result[MAXLINE];  /* store string after replacement */ 

    while ( readLine(buffer, MAXLINE) > 0 )
    {
        detab(result, buffer);
        printf("%s\n", buffer);
        printf("%s\n", result);
    }

    return 0;
}





