#include <stdio.h>

int main (void)
{
    char *array[] = { "hello", "world", "bye" };

    printf("%s\n", *array);
    printf("%s\n", *(array+1));

    return 0;
}

