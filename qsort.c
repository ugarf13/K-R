/* Implementation of quicksort */

#include <stdio.h>

int  main (void)
{
    int   z[] = { 3, 1, 2 , 5, -3};
    void  qsort (int v[], int left, int right);
    void  displayArray (int v[], int lim);

    displayArray(z, 5);
    qsort(z, 0, 4);
    displayArray(z, 5);

    return 0;
}

void  qsort (int v[], int left, int right)
{
    int   i, last;
    void  swap (int v[], int i, int j);

    if ( left >= right )
        return;
    swap(v, left, (left + right) / 2);
    last = left;

    for ( i = left + 1; i <= right; ++i )
        if ( v[i] < v[left] )
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void  displayArray (int v[], int lim)
{
    int  i;

    printf("\{");
    for ( i = 0; i < lim; ++i ) {
        printf("%d", v[i]);
        if ( i < lim - 1 )
            printf(", ");
    }
    printf("\}\n");
}
    

void  swap (int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
