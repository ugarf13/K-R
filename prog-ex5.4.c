#include <stdio.h>

int main (void)
{
    char  s[80] = "hello";
    char  t[] = "hihello";
    int  strend (char *s, char *t);

    if ( strend(s, t) )
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}

/* strend: return 1 if t occurs at the end of s */
int  strend (char *s, char *t)
{
    char *bs, *bt;

    bs = s;
    bt = t;
    while ( *s )
        s++;
    while ( *t )
        t++;
    if ( t - bt > s - bs )
        return 0;
    while ( s >= bs && t >= bt ) {
        if ( *t-- != *s-- )
            return 0;
    }
    return 1;
}

