/* atof with scientific notation */

#include <stdio.h>
#include <ctype.h>

#define  MAXLINE  100 /* max length of string */

int  main (void)
{
    char    s[] = "123.45e6";
    double  atof (char s[]);
    
    printf("%g\n", atof(s)); 
    
    return 0;
}

double  atof (char s[])
{
    double  val, power, epower;
    int     i, sign, isE = 0;
    int     esign, exponent;

    for ( i = 0; isspace(s[i]); ++i ) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;

    if ( s[i] == '-' || s[i] == '+' )
        ++i;  /* move beyond sign char */

    for ( val = 0.0; isdigit(s[i]); ++i )
        val = 10.0 * val + (s[i] - '0');
    
    if ( s[i] == '.')
        ++i;
    
    for ( power = 1.0; isdigit(s[i]); ++i ) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    /* handle the scientific notation */
    if ( s[i] == 'e' || s[i] == 'E') {
        ++i;
        isE = 1;

        esign = (s[i] == '-') ? -1 : 1;
        if ( s[i] == '-' || s[i] == '+' )
            ++i;
       
        /* transform exponent to int */
        for ( exponent = 0; isdigit(s[i]); ++i )
            exponent = 10 * exponent + (s[i] - '0');

        for ( epower = 1.0 ; exponent >= 1; --exponent )
            epower *= 10.0;
    }

    if ( isE && esign < 0 )
        return sign * val / (power * epower);
    else if ( isE && esign > 0 )
        return sign * val * epower / power;
    else 
        return sign * val / power;
}



