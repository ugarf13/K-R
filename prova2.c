#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
    printf("%s\n", argv[0]); // print argv[0];
    printf("%s\n", *++argv); // print argv[1];
    printf("%s\n", *++argv); // print argv[2];

    printf("%s\n", argv[0]); // still prints argv[2] because pointer now points to it */

    return 0;
}

