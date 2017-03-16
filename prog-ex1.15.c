/* Print fahr to celsius table 
 * for fahr = 0, 20,..., 300; floating-point version*/

#include <stdio.h>

/* celsius: function to convert fahr to celsius */
float  fahrToCelsius ( float fahr )
{
    return 5.0 * (fahr - 32.0) / 9.0;
}


int main (void)
{
    float  fahrToCelsius ( float fahr );
    int    lower, upper, step;
    float  fahr;

    lower = 0;   /* lower bound on fahr temperature */
    upper = 300; /* upper bound on fahr temperature */
    step  = 20;  /* increment size */

    printf("Fahr   Celsius\n");
    printf("----   -------\n");

    for ( fahr = lower; fahr <= upper; fahr += step )
        printf("%3.0f   %6.1f\n", fahr, fahrToCelsius(fahr));

    return 0;
}
