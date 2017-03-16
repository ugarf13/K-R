/* recursive version of itoa */

#include <stdio.h>

int main (void)
{
    int   n = -53173;
    char  s[10];
    void  itoa (int y, char t[]);
    
    itoa(n, s);
    printf("%s\n", s);
}


/* itoa: convert decimal n to characters in s */
void  itoa (int y, char t[])
{
    int         sign;
    static int  index; /* currently available slot */
    
    if ( (sign = y) < 0 ) { /* only trigger once if at all */
        t[index++] = '-';   /* because any other invocation is with positive y */
        y = -y;
    }

    if ( y / 10 ) 
        itoa(y / 10, t);
    t[index++] = y % 10 + '0';
    t[index] = '\0';
}


