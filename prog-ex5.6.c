#include <stdio.h>

#define  MAXLINE  1000  /* max length of a line */

int   mygetline (char *line, int max);
int   strindex (char *source, char *searchfor);

char pattern[] = "hello"; /* pattern to search for */

/* find all lines matching pattern */
int main (void)
{
    char  line[MAXLINE];
    int   found = 0;
    
    while ( mygetline(line, MAXLINE) > 0 ) /* is length of line > 0? */
        if ( strindex(line, pattern) >= 0 ) {
            printf("%s", line);
            found++;
        }
    return found;
}

/* mygetline: get line into s, return length */
int  mygetline (char *line, int max)
{
    int   c;     /* used to store each new char */
    char  *bline; /* remember beginning of line */

    bline = line;
    while ( max-- > 0 && (c = getchar()) != EOF && c != '\n' )
        *line++ = c;
    if ( c == '\n' )
        *line++ = c;
    *line = '\0';
    return line - bline;
}

/* strindex: return index of searchfor in source, -1 if not found */
int  strindex (char *source, char *searchfor)
{
    char *index;      /* current position tested in source */
    char *bsource = source;    /* remember beginning of source string */
    char *bsearchfor = searchfor; /* beginning of searchfor */        

    for ( ; *source != '\0'; source++ ) {
        index = source;
        //printf("current index = %i\n", source - bsource);
        searchfor = bsearchfor;
        for ( ; *index == *searchfor && *index != '\0' && *searchfor != '\0'; ) {
            index++; 
            searchfor++; 
        }
        if ( searchfor > bsearchfor && *searchfor == '\0' ) 
            /* we reached end of searchfor successfully */
            return source - bsource; 
    }
    return -1;
}













