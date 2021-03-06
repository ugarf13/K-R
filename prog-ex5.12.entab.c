#include <stdio.h>
#include <stdlib.h>

#define  TABINC 8 /* default tab increment */
#define  MAXLINE 100  

int main (int argc, char *argv[])
{
    char  tabs[MAXLINE];  //{ 0, 8, 20, 25, 32, 55, 70, 78, 90, 100 };

    void  settab (char *tabs, int argc, char *argv[]);
    void  entab (char *tabstop);

    settab(tabs, argc, argv);
    entab(&tabs[1]);

    return 0;
}

/* entab: replace tabs with blanks */
void  entab (char *tabstop)
{
    int   c;
    int   nb = 0;      /* number of blank spaces */
    int   nt = 0;      /* number of tabs */
    int   pos = 0;     /* current position */
    char  *b = tabstop; /* remember beginning of tab list */

    while ( (c = getchar()) != EOF ) {
        if ( c == ' ' ) {
            if ( pos >= *(tabstop - 1) && pos + 1  < *tabstop ){
                nb++;
            } else { /* with current blank, I would reach next tabstop */
                nb = 0;
                nt++; /* forget about blanks, and put in a tab */
                ++tabstop; /* update tabstop */
            }
            ++pos; /* update position */
        } else if ( c == '\t' ) {
            nb = 0; /* forget about blanks */
            nt++;   /* put in a tab */
            ++tabstop; /* update tabstop */
            pos = *tabstop;
        } else {
            for ( ; nt > 0; nt-- )
                //putchar('\t');
                printf("t");
            for ( ; nb > 0; nb-- )
                //putchar(' ');
                printf("s");
            putchar(c);
            if ( c == '\n' ) {
                pos = 0;
                tabstop = b; /* reset tab list */
            } else {
                if ( ++pos >= *tabstop ) /* update position and possibly tabstop */
                    ++tabstop;
            }
        }
    }
}
           
/* settab: sets tab stops based on command line inputs and store in tabs */
void  settab (char *tabs, int argc, char *argv[])
{
    int  tabstop;
    int  n = TABINC; 
    int  c;
    
    *tabs++ = 0;
    while ( --argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+') ) {
        switch (c) {
            case '-': 
                tabstop = atoi(++argv[0]);
                *tabs++ = tabstop;
                //printf("m = %s\n", argv[0]);
                break;
            case '+':
                n = atoi(argv[0]);
                //printf("n = %i\n", n);
                break;
            default:
                printf("error: illegal option\n");
                break;
        }
    }

    //printf("%i ", *(tabs-1));
    while ( tabstop <= MAXLINE ) {
        tabstop += n;
        //printf("%i ", tabstop);
        *tabs++ = tabstop;
    }
}

        

