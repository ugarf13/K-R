/* Program to expand shorthand notations like a-z, A-Z, or, 0-9, nothing else */

#include <stdio.h>
#include <ctype.h>

#define  MAXLINE  150 /* max length of string */

int  main (void)
{
    char s1[] = "M-a, 0-M, M-0";
    char s2[MAXLINE];
    void  expand (char s1[], char s2[]);

    expand(s1, s2);

    printf("Original: %s\n", s1);
    printf("Expanded: %s\n", s2);

    return 0;
}

/* expand: expands shorthand notation */
void  expand (char s1[], char s2[])
{
    int   i, j;
    char  k;

    for ( i = 0, j = 0; s1[i] != '\0'; ++i ) {
        if ( i > 0 ) {
            k = s1[i - 1]; /* save previous char */
            //s2[j - 1] = k;
        } else 
            k = '\0';

        if ( s1[i] == '-' && k != '\0' ) {
            if ( !isalnum(k) ) /* nothing to expand */
                s2[j++] = s1[i]; 
            else if ( ( (isalpha(k) * isalpha(s1[i + 1]) > 0 
                            && (islower(k) * islower(s1[i + 1]) > 0 ))
                      || (isalpha(k) * isalpha(s1[i + 1]) > 0 
                            && (isupper(k) * isupper(s1[i + 1]) > 0 ))
                      || (isdigit(k) * isdigit(s1[i + 1]) > 0))  
                      && k < s1[i + 1] ) { 
                ++k; /* move to char after k, because has already been copied */
                while ( k <= s1[i + 1] )
                    s2[j++] = k++;
                ++i; /* i further increases by 1 as loop restarts */
            } else 
                s2[j++] = s1[i];
        } else
            s2[j++] = s1[i];

    }
    s2[j] = '\0';
}



