#include <stdio.h>
#include <string.h>

#define  MAXLINE 1000

int mygetline(char *line, int maxline);

/* find: print lines that match pattern from 1st arg */
int main (int argc, char *argv[])
{
    char  line[MAXLINE];
    long  linenum = 0;
    int   c, except = 0, number = 0, found = 0;

    while ( --argc > 0 && (*++argv)[0] == '-' )
        while ( (c = *++argv[0]) ) // *++(*argv)) )
            switch (c) {
                case 'x':
                    except = 1; /* turn on except flag */
                    break;
                case 'n':
                    number = 1; /* turn on line numbering flag */
                    break;
                default:
                    printf("myfind: illegal option %c\n", c);
                    argc = 0; /* exit outer while loop */
                    found = -1;
                    break;
            }
    if ( argc != 1 )
        printf("Usage: find -x -n pattern\n");
    else
        while ( mygetline(line, MAXLINE) > 0 ) {
            linenum++;
            if ( (strstr(line, *argv) != NULL) != except ) {
                if ( number )
                    printf("%ld: ", linenum);
                printf("%s\n", line);
                found++;
            }
        }
}


int  mygetline (char *line, int maxline)
{
    int   c;
    char  *b = line;
    while ( maxline-- > 0 && (c = getchar()) != EOF && c != '\n' )
        *line++ = c;
    *line = '\0';
    return line - b;
}



