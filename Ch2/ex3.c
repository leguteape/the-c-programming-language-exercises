/*
 * Function (and driver main) to convert a string of
 * hexadecimal digits into equivalent int value.
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>

/*
 * NAME: htoi
 * PURPOSE: Function to convert a string of
 *          hexadecimal digits into equivalent int value.
 * PARAMETERS:
 *      - char hex_string[]: The string of hex digits to convert to int.
 * RETURNS: The converted integer value.
 */
int htoi(char hex_string[]);

int main(void) {
    char hexstr1[] = "0x123abc";
    char hexstr2[] = "0X123abc";
    char hexstr3[] = "123abc";
    char hexstr4[] = "g123abc";

    assert(1194684 == htoi(hexstr1));
    assert(1194684 == htoi(hexstr2));
    assert(1194684 == htoi(hexstr3));
    assert(0 == htoi(hexstr4));

    return 0;
}

int htoi(char s[]) {
    int n = 0;
    // Skip initial 0x or 0X if any
    int i = s[0] == '0' && ((s[1] == 'x') || (s[1] == 'X')) ? 2 : 0;

    for (; s[i] != '\0'; ++i)
        if (isdigit(s[i]))
            n = n * 16 + (s[i] - '0');
        else if (s[i] == 'A' || s[i] == 'B' || s[i] == 'C' || s[i] == 'D' ||
                 s[i] == 'E' || s[i] == 'F')
            n = n * 16 + (10 + s[i] - 'A');
        else if (s[i] == 'a' || s[i] == 'b' || s[i] == 'c' || s[i] == 'd' ||
                 s[i] == 'e' || s[i] == 'f')
            n = n * 16 + (10 + s[i] - 'a');
        else
            // Return current value of n if illegal hex digit found
            return n;
    return n;
}
