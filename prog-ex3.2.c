/* Program to return a copy of a string in which \n and \t 
 * are converted into visible escape sequences */

#include <stdio.h>

#define MAXLINE  100 /* maximum length of input string */

int main (void)
{
    char  s1[MAXLINE] = "\thello\nworld!";
    char  s2[MAXLINE];
    void  escape (char s1[], char s2[]);
    void  descape (char s1[], char s2[]);

    escape(s1, s2);
    printf("%s\n%s\n", s1, s2);

    descape(s2, s1);
    printf("%s\n%s\n", s2, s1);


    return 0;
}

/* descape: function to convert some escaped sequences into escaped chars */
void  descape (char s1[], char s2[])
{
    int  i, j;

    i = j = 0;
    while ( s1[i] != '\0' ) {
        switch ( s1[i] ) {
            case '\\':
                if ( s1[i + 1] == 'n' ) {
                    s2[j] = '\n';
                    ++i;
                } else if ( s1[i + 1] == 't' ) {
                    s2[j] = '\t';
                    ++i;
                } else 
                    s2[j] = '\\';
                break;
            default:
                s2[j] = s1[i];
                break;
        }
        ++i;
        ++j;
    }
    s2[j] = '\0';
}

/* escape: function to convert escape chars into escape sequences */
void  escape (char s1[], char s2[])
{
    int  i, j;

    i = j = 0;
    while ( s1[i] != '\0' ) {
        switch ( s1[i] ) {
            case '\n':
                s2[j++] = '\\';
                s2[j] = 'n';
                break;
            case '\t':
                s2[j++] = '\\';
                s2[j] = 't';
                break;
            default:
                s2[j] = s1[i];
                break;
        }
        ++i;
        ++j;
    }
    s2[j] = '\0';
}

