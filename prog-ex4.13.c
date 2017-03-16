/* version of reverse using recursion */

#include <stdio.h>
#include <string.h>

int main (void)
{
    char  s[] = "!dlrow olleh";
    void  reverse (char t[]);
    
    printf("%s\n", s);
    reverse(s);
    printf("%s\n", s);

    return 0;
}


/* reverse: reverse string s in place */
void  reverse (char t[])
{
    int         temp, len;
    static int  i;

    len = strlen(t);

    if ( i < len - i - 1 ) {
        temp = t[i];
        t[i] = t[len -i - 1];
        t[len - i - 1] = temp;
        ++i;
        reverse(t);
    }
}
