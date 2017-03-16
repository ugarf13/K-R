#include <stdio.h>

int main (void)
{
    char  s[80] = "hello ";
    char  t[] = "world!";
    void  mystrcat (char *s, char *t);

    mystrcat(s, t);

    printf("%s\n", s);

    return 0;
}

/* mystrcat: concatenate t to the end of s */
void  mystrcat (char *s, char *t)
{
    while ( *s )
        s++;
    while ( (*s++ = *t++) )
        ;
}

