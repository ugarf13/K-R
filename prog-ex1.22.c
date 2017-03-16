/* Program to fold long input lines into one or more shorter lines after the
 * last non-blank character that occurs before the n-th column of input */

/* Tabs are handled in the following way: First store the entire input in a
 * buffer, then expand the tabs with blanks, so only blanks are present */

/* Program is inefficient because it stores the entire input, it would be
 * better to store only a line*/

#include <stdio.h>

#define MAXLINE   1000  /* maximum number of characters */
#define MAXCOL    20    /* maximum number of chars in a line */
#define TABSPACE  8     /* number of columns between tabs */

/* displayLine: display a slice of a char string */
void  displayLine ( char  line[], int  start, int  end )
{
    int  i;

    for ( i = start; i < end && line[i] != '\0' ; ++i )
        printf("%c", line[i]);
    putchar('\n');
}

/* findLastBlank: returns index of last occurrence of blank space within
 * specified string slice */
int findLastBlank ( char  line[], int  start , int  end)
{
    int  i;
    int  blank = -1;

    for( i = 0; (i < end - start) && line[start + i] != '\0'; ++i ) {
        if ( line[start + i] == ' ' )
            blank = i;
    }

    return blank;
}

/* findNewline: return index of first occurrence of newline within string slice
 * */
int  findNewline ( char  line[], int  start, int  end )
{
    int  i;

    for( i = 0; (i < end - start) && line[start + i] != '\0'; ++i ) {
        if ( line[start + i] == '\n')
            return i; /* return index of newline */
    }

    return -1; /* newline not found */
}

int  expandTabs ( char result[], char line[] )
{
    int  i = 0, pos = 0;
    int  nb = 0;

    for ( ; line[i] != '\0'; ++i ) {
        if ( line[i] == '\t' ) {
            nb = TABSPACE - pos % TABSPACE;

            while ( nb > 0 ) {
                result[pos] = ' ';
                ++pos;
                --nb;
            }
        } else {
            result[pos] = line[i];
            ++pos;
        }
    }
    result[pos] = '\0';
    return pos; /* return length of 'result' */
}

int  ignoreInitialBlanks ( char  line[] , int  start )
{
    int  i;

    for( i = start; (i < start + MAXCOL) && line[i] != '\0'; ++i ) {
        if ( line[i] != ' ')
            return i; /* return index of newline */
    }

    return start; 
} 


int main (void)
{
    int   c;
    int   i, start, end, endOfBuffer;
    int   indexBlank, indexNewline;
    char  buffer[MAXLINE];    /* store input */
    char  expBuffer[MAXLINE]; /* store buffer with tabs expanded */
    void  displayLine ( char  line[], int  start, int  end );
    int   findLastBlank ( char  line[], int  start, int  end );
    int   findNewline ( char  line[], int  start, int  end );
    int   expandTabs ( char result[], char line[] );
    int   ignoreInitialBlanks ( char  line[] , int  start );
    
    i = 0;
    while ( (c = getchar()) != EOF && i < MAXLINE - 1) {
        buffer[i] = c;
        ++i;
    }
    buffer[i] = '\0';
    endOfBuffer = expandTabs( expBuffer, buffer);
    printf("\n");
    //printf("%s", buffer);
        
    start = 0;
    while ( start < endOfBuffer ) {
        /* start a line for first non-blank char */
        start = ignoreInitialBlanks(expBuffer, start);

        /* check whether there is a newline before end of line */
        indexNewline = findNewline(expBuffer, start, start + MAXCOL);
        //printf("%i\n", indexNewline);
        
        /* find last blank space before end of line */
        indexBlank = findLastBlank(expBuffer, start, start + MAXCOL);
        //printf("%i\n", indexBlank);
        
        if ( indexNewline > -1 ) { /* newline found */
            //if ( last_c == '\n' )
            end = start + indexNewline; 
            displayLine(expBuffer, start, end); /* display until end-1 */
            start = end + 1; /* restart from next char */
        } else if ( indexBlank == MAXCOL - 1 || indexBlank == -1 ) {
            end = start + MAXCOL;
            displayLine(expBuffer, start, end); /* already contains a break in case of EOF */
            start = end;
        } else if ( indexBlank < MAXCOL -1 ) {
            if ( start + MAXCOL >= endOfBuffer )
                end = start + MAXCOL;
            else
                end = start + indexBlank;
            displayLine(expBuffer, start, end);
            start = end + 1;
        }

    }

    return 0;

}

