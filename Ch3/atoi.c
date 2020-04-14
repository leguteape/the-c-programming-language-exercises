/*
 * Function (and driver main) to convert a string of
 * hexadecimal digits into equivalent int value.
 */

#include <assert.h>
#include <ctype.h>

/*
 * NAME: strtoi
 * PURPOSE: Function to convert a string of
 *          digits into equivalent int value.
 * PARAMETERS:
 *      - char string[]: The string of hex digits to convert to int.
 * RETURNS: The converted integer value.
 */
int strtoi(char string[]);

int main(void) {
    char hexstr1[] = "12345";
    char hexstr2[] = "235234";
    char hexstr3[] = "454424";
    char hexstr4[] = "g123abc";

    assert(12345 == strtoi(hexstr1));
    assert(235234 == strtoi(hexstr2));
    assert(454424 == strtoi(hexstr3));
    assert(0 == strtoi(hexstr4));

    return 0;
}

int strtoi(char s[]) {
    int i, n;

    // Skip leading whitespace
    for (i = 0; isspace(s[i]); i++)
        ;

    int sign = (s[i] == '-') ? -1 : 0;
    // Skip the sign, if present
    if (s[i] == '+' || s[i] == '-') i++;
    // Compute the int value for digits
    for (n = 0; isdigit(s[i]); i++) n = n * 10 + (s[i] - '0');

    return sign * n;
}
