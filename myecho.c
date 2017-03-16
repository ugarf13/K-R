#include <stdio.h>

int main (int argc, char *argv[])
{
    char *end = argv + argc;
    while ( ++argv < end ) 
        printf("%s%s", *argv, (argv < end) ? " " : "");
    printf("\n");
    return 0;
}



