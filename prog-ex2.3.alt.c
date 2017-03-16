/* Program to convert a string of hexadecimal digits 
 * into its equivalent integer value */

#include <stdio.h>

int  htoi ( char s[] )
{
    int  i, n;
    int  result;

    i = 0;
    if ( s[i] == '0' ){
        ++i;
        if ( s[i] == 'x' || s[i] == 'X' )
            ++i; /* string starts with 0x, so skip first 2 chars */
    }
    
    result = 0; /* var to store converted number */
    for ( ; s[i] != '\0'; ++i ) { /* start from last digits */
        if ( s[i] >= '0' && s[i] <= '9' ) /* char is a digit */
            n = s[i] - '0'; /* transform digit into equivalent integer */
        else if ( (s[i] >= 'a' && s[i] <= 'f') )
            n = s[i] - 'a' + 10;
        else if ( (s[i] >= 'A' && s[i] <= 'F') )
            n = s[i] - 'A' + 10;
        else { 
            printf("Error: Number is not hexadecimal.\n");
            return -1;
        }

        result = result * 16 + n;
    }
    return result;
}

int main (void)
{
    char  s[10];
    int  htoi ( char s[] );
    int  result;

    printf("Enter hexadecimal number: ");
    scanf("%s", s); getchar();
    
        if ( (result = htoi(s)) > -1 )
        printf("Decimal form: %i\n", result);

    return 0;
}







