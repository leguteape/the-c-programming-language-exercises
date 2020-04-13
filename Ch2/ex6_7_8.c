/*
 * Program to do useful things with bitwise operators.
 */

#include <assert.h>
#include <stdio.h>

/*
 * NAME: setbits
 * PURPOSE: To set the 'count' bits of 'dest' from given' position'
 *          to the rightmost 'count' bits of 'src'.
 * PARAMETERS:
 *      - unsigned dest: The number whose bits to set
 *      - int position: The position in 'dest' from which to start setting
 *      - int count: The number of bits to set (right-aligned)
 *      - unsigned src: The number whose rightmost 'count' bits are used
 * RETURNS: The value of 'dest' after setting.
 */
unsigned setbits(unsigned dest, int position, int count, unsigned src);

/*
 * NAME: invert
 * PURPOSE: To invert 'count' bits of 'number' from given 'position'
 *          (right-aligned) while leaving others unchanged.
 * PARAMETERS:
 *      - unsigned number: The number whose bits to invert
 *      - int position: The position in 'number' from which to start inverting
 *      - int count: The number of bits to set (right-aligned)
 * RETURNS: The value of 'number' after inversion.
 */
unsigned invert(unsigned number, int position, int count);

/*
 * NAME: rightrot
 * PURPOSE: To rotate an integer 'number' right by 'count' positions.
 * PARAMETERS:
 *      - unsigned number: the number whose value to rotate right
 *      - int count: The number of bits to rotate by
 * RETURNS: The value of 'number' after rotation.
 */
unsigned rightrot(unsigned number, int count);

int main(void) {
    assert(setbits(0xf7, 6, 4, 0x1) == 0x8f);
    assert(invert(0xe6, 5, 5) == 0xd8);
    assert(rightrot(0x96, 3) == 0xc0000012);

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (x & ~(~(~0 << n) << (p - n + 1))) |
           ((y & ~(~0 << n)) << (p - n + 1));
}

unsigned invert(unsigned x, int p, int n) {
    return x ^ ~(~0 << n) << (p - n + 1);
}

unsigned rightrot(unsigned x, int n) {
    return (x >> n) | ((x & ~(~0 << n)) << ((sizeof(x) * 8 - 1) - n + 1));
}
