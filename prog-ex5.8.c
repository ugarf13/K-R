#include <stdio.h>

static char daytab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int main (void)
{
    int   month, day;
    int   day_of_year (int year, int month, int day);
    void  month_day (int year, int yearday, int *pmonth, int *pday);
    
    printf("%i\n", day_of_year(2016, 3, 13)); 
    month_day(2016, 31+29+13, &month, & day);
    printf("%i/%i\n", month, day);

    return 0;
}

/* day_of_year: set day of year from month and day */
int  day_of_year (int year, int month, int day)
{
    int  leap;
    char  *p;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    p = daytab[leap];
    while ( --month ) 
        day += *++p; /* increment first because first element is zero */

    return day;
}

/* month_day: set month, day from day of year */
void month_day (int year, int yearday, int *pmonth, int *pday)
{
    int   leap;
    char  *p, *bp;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    p = *(daytab + leap) + 1;
    bp = p;
    while ( yearday > *p ) 
        yearday -= *p++;
    *pmonth = ++p - bp;
    *pday = yearday;
}
