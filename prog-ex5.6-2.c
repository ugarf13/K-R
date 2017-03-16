#include <stdio.h>
#include <string.h>

int main (void)
{
    int   n = -123;
    char  s[20];
    void  itoa (char *s, int n);
    
    itoa(s, n);
    printf("%s\n", s);

    return 0;
}


/* itoa: convert integer to s */
void  itoa (char *s, int n)
{
    int   sign;
    char  *t = s;  /* remember beginning of string s */
    void  reverse (char *s);

    if ( n < 0 ) {
        sign = -1;
        n = -n;
    }
    do {
        *s++ = n % 10 + '0';
    } while ( (n = n / 10) );
    if ( sign < 0 )
        *s++ = '-';
    *s = '\0';
    reverse(t);
}

/* reverse: reverse string s */
void  reverse (char *s)
{
    char  temp;
    char  *end = s + (strlen(s) - 1); /* pointer to last char in s */  
    
    for ( ; s < end ; s++, end-- ) {
        temp = *s;
        *s = *end;
        *end = temp;
    }
}



