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
 *  - int min_field_width: The minimum number of characters to have in string
 * RETURNS: Nothing.
 */
void itoa(int number, char string[], int min_field_width);

int main(void) {
    char str[MAXLEN];

    itoa(23443, str, 8);
    assert(strcmp(str, "   23443") == 0);
    itoa(-23443, str, 3);
    assert(strcmp(str, "-23443") == 0);
    itoa(INT_MAX, str, 20);
    assert(strcmp(str, "          2147483647") == 0);
    itoa(INT_MIN, str, 25);
    assert(strcmp(str, "              -2147483648") == 0);

    return 0;
}

void itoa(int n, char s[], int w) {
    int i = 0, sign = n;

    do {
        s[i++] = (n < 0) ? -(n % 10) + '0' : n % 10 + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) s[i++] = '-';
    // Insert blank spaces to fill at least the minimum field width
    if (i < w)
        for (int j = w - i; j > 0; j--) s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}
