#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    double v1, v2;
    char s1[] = "hello";
    char s2[] = "world";

    v1 = atof(s1);
    v2 = atof(s2);
    printf("v1 = %f, v2 = %f\n", v1, v2);

    return 0;
}

