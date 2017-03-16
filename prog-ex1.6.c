#include <stdio.h>

int main (void)
{
    int  c;

    while ( c = getchar() != EOF )
        printf("%i\n", c);
    printf("%i - at EOF\n", c);

    return 0;
}

