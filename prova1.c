#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
    int   c;
    char  *s;
    while ( --argc > 0 ) {
        s = *++argv;
        printf("%s\n", s);
        while ( c = *s++ )
            printf("%c\n", c);
    }

    return 0;
}

