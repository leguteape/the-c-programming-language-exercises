/*
 * Program to convert an integer into a base b character
 * representation in string.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>

#include "../include/strutils.h"

#define MAXLEN 100

/*
 * NAME: itob
 * PURPOSE: To convert an integer to a base b character in the string.
 * PARAMETERS:
 *  - int number: The number to convert to string
 *  - char string[]: The string buffer
 *  - int base: The base to convert to
 * RETURNS: Nothing.
 */
void itob(int number, char string[], int base);

int main(void) {
    char str[MAXLEN];

    itob(23443, str, 8);
    assert(strcmp(str, "055623") == 0);
    itob(-23443, str, 16);
    assert(strcmp(str, "-0x5b93") == 0);
    itob(INT_MAX, str, 16);
    assert(strcmp(str, "0x7fffffff") == 0);
    itob(INT_MIN, str, 8);
    assert(strcmp(str, "-020000000000") == 0);

    return 0;
}

void itob(int n, char s[], int b) {
    int i = 0, sign = n;
    int digit;

    do {
        digit = (n < 0) ? -(n % b) : n % b;
        s[i++] = (digit >= 10) ? digit - 10 + 'a' : digit + '0';
    } while ((n /= b) != 0);
    // Add formatting characters according to the base
    if (b == 2)
        s[i++] = 'b', s[i++] = '0';
    else if (b == 8)
        s[i++] = '0';
    else if (b == 16)
        s[i++] = 'x', s[i++] = '0';
    // If number is negative, add a '-' sign
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
