/* Program that takes an int and return it with the n bits that begin at
 * position p inverted, that is, just complementing a slice of bits, leaving the
 * others unchanged.
 *
 * The leftmost, significant, digit is at position 0 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main (void)
{
    int           start_bit = 2;
    int           count = 3;
    unsigned int  w1 = 0xe1f4;
    void          displayBinary ( unsigned int  x );
    void          invert        ( unsigned int  *source, 
                                  int start_bit,
                                  int  count);

    printf("source: %i = ", w1);
    displayBinary(w1);

    invert(&w1, start_bit, count);
    
    printf("set to: %i = ", w1);
    displayBinary(w1);

    return 0;
}

void  invert ( unsigned int  *source, 
               int  start_bit, 
               int  count )
{
    int   i; /* index list */
    int   size;
    int   source_len;
    int   start_source;
    int   int_size ( void );
    void  displayBinary ( unsigned int  x );
    unsigned int mask;
    unsigned int bits;

    size = int_size();
   
    /* search for beginning of binary rep of source w/o initial 0s */
    i = 0;
    while ( i < size ) {
        if ( *source >> (size - i - 1) ) {
            start_source = i;
            break;
        } else 
            ++i;
    }
    //printf("%i\n", start_source);
    //printf("after: %i\n", *source);

    source_len = size - start_source; /* effective number of bits in source */
    
    if ( start_bit >= source_len ) {
        printf("Starting bit out of range.\n");
        exit(0);
    } else {  /* if count leads after rightmost, stop at rightmost (included) */
        if ( start_bit + count > source_len)
            count = source_len - start_bit;
    }

    /* mask all bits before start_bit */
    bits = *source << (start_source + start_bit); /* shift left first */
    /* all shifted bits are 0ed, if we then shift right again*/
    
    /* complement the bits now that they are left adjusted */
    bits = ~bits;

    /* shift right so that last bit of interest becomes the rightmost */
    bits >>= size - count; /* this clears the right-hand side of desired bits */

    /* move bits back to intial location */
    bits <<= size - start_source - start_bit - count;
    
    /* create mask that is zero only at the target bits */
    mask = ~(~0 << count);
    mask <<= size - (start_source + start_bit + count);
    mask = ~mask;

    /* clear up the target bits */
    *source &= mask;

    /* insert pattern to target bits */
    *source |= bits;
}

/* Function to display binary representation of an int */
void  displayBinary ( unsigned int  x )
{
    int   i;
    int   bit;
    bool  inside = false; /* flag to signal when inside proper binary rep */ 
    int   int_size ( void );

    i = 1;
    while ( i <= int_size() ) {
            /* shift leftmost digit, second leftmost, etc., to rightmost */
            /* extract rightmost digit */            
            bit = x >> (int_size() - i);
            if ( bit ) /* inside */
                inside = true;
            if ( inside ) /* start displaying. It skips initial 0s */
                printf("%i", bit  & 1);
        ++i;
    }

    printf("\n");
}


/* Function to compute the size of an int in the current machine */

int int_size ( void )
{
    unsigned int  x = ~0;
    int           result = 0;

    while ( x ) {
        result += x & 1;
        x >>= 1;
    }

    //printf("int size = %i\n", result);

    return result;
}

