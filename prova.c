#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>

int main (void)
{
    char    str[] = "hello world!";
    char    *chararray[] = { "123", "35" };
    size_t  mystrlen (char *s);

    //printf("%c\n", isprint(c));
    //printf("%i\n", isalpha(c) * isalpha(d) > 0);
    //printf("%i\n", isalpha(c) * isalpha(e) > 0 );
    //printf("%i\n", isdigit(e) * isdigit(f) > 0);

    //printf("%c\n", tolower(c));
    //printf("%c\n", tolower(e));

    //signed int  x = ~0;
    //if ( x == -1 )
    //    printf("Two's complement notation\n");
    //else 
    //    printf("One's complement notation\n");

    //signed int  n = -2147483648;
    //int         i = 0;
    //char        s[10];

    //n = (n < 0) ? -n : n;
    //do {
    //    s[i++] = abs(n % 10) + '0';
    //    n /= 10;
    //} while ( n != 0 );
    
    //s[i] = '\0';

    //printf("%s\n", s);

    //printf("\nThe length of \"%s\" is %lu.\n", str, mystrlen(str));
    //printf("%c\n", *++chararray[1]);

    char *s = ++chararray;
    printf("%s\n", *s);
    
    return 0;
}

int  abs (int x)
{
    return (x < 0) ? -x : x;
}

size_t  mystrlen (char *s)
{
    char  *p = s;

    while ( *p != '\0' )
        p++;
    return p - s;
}


