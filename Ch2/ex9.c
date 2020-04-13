/*
 * Program to count the number of set bits (1s)
 * using a 2's complement property.
 */

#include <assert.h>

/*
 * NAME: bitcount
 * PURPOSE: Find the number of set bits (1s) in a number.
 * PARAMETERS:
 *  - unsigned number: The number whose bits to count
 * RETURNS: The count of set bits.
 */
int bitcount(unsigned number);

int main(void) {
    assert(bitcount(0xaa) == 4);
    assert(bitcount(0b0101010) == 3);

    return 0;
}

int bitcount(unsigned x) {
    int n;

    // Doing x &= x - 1  clears the rightmost 1
    // at whatever position it may be in
    // for 2's complement numbers.
    for (n = 0; x != 0; x &= x - 1) ++n;

    return n;
}
