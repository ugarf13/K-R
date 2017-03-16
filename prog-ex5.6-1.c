#include <stdio.h>

int main (void)
{
    char  str[] = "123";
    int   atoi (char *s);

    printf("%i\n", atoi(str));

    return 0;
}


/* atoi: convert s to integer */
int  atoi (char *s)
{
    int  n = 0;

    for ( ; *s != '\0' && *s >= '0' && *s <= '9'; s++ )
        n = 10 * n + (*s - '0');
    return n;
}

