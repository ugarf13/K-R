/* print a decimal number n */

#include <stdio.h>


int  main (void)
{
    int   n = -123;
    void  printd (int n);

    printd(n);
    putchar('\n');
}

void  printd (int n)
{
    if ( n < 0 ) {
        putchar('-');
        n = -n;
    }

    if ( n / 10 ) 
        printd(n / 10);
    putchar(n % 10 + '0');
}


