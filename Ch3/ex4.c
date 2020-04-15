/*
 * Program to convert integer to string using do-while.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>

#include "../include/strutils.h"

#define MAXLEN 100

/*
 * NAME: itoa
 * PURPOSE: Convert an integers to characters in a string.
 * PARAMETERS:
 *  - int number: The number to convert to string
 *  - char string[]: The target string
 * RETURNS: Nothing.
 */
void itoa(int number, char string[]);

int main(void) {
    char str[MAXLEN];

    itoa(23443, str);
    assert(strcmp(str, "23443") == 0);
    itoa(-23443, str);
    assert(strcmp(str, "-23443") == 0);
    itoa(INT_MAX, str);
    assert(strcmp(str, "2147483647") == 0);
    itoa(INT_MIN, str);
    assert(strcmp(str, "-2147483648") == 0);

    return 0;
}

void itoa(int n, char s[]) {
    int i = 0, sign = n;
    int digit;

    do {
        digit = n % 10;
        s[i++] = (digit < 0) ? -digit + '0' : digit + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
