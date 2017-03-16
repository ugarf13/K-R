#include <stdio.h>
#include <stdlib.h>

#define  TABINC 8 /* default tab increment */
#define  MAXLINE 100  

int main (int argc, char *argv[])
{
    char  tabs[MAXLINE];  // ex: { 0, 8, 20, 25, 32, 55, 70, 78, 90, 100 };

    void  settab (char *tabs, int argc, char *argv[]);
    void  detab (char *tabstop);

    settab(tabs, argc, argv);
    detab(tabs);

    return 0;
}

/* detab: replace tabs with blanks */
void  detab (char *tabstop)
{   
    int   c;
    int   nb = 0;       /* number of blank spaces */
    int   pos = 0;      /* current position */
    char  *b = tabstop;  /* remember beginning of tab list */

    while ( (c = getchar()) != EOF ) {
         if ( c == '\t' ) {
            if ( pos > *tabstop )
                while ( pos > *++tabstop )
                    ;
            nb = *tabstop - pos % *tabstop;
            pos = pos + nb;
            while ( nb-- > 0 )
                //putchar(' ');
                putchar('s');
        } else if ( c == '\n' ) {
            pos = 0;
            tabstop = b; /* reset the tab list */
            putchar(c);
        } else {
            ++pos;
            putchar(c);
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
      


        

