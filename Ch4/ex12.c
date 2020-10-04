/*
 * Program to convert integer to string using recursive function.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>

#define MAXLEN 1000

/*
 * NAME: itoa_recursive
 * PURPOSE: To convert an integer to string.
 * PARAMETERS:
 *  - int number: The number to convert to string
 *  - char string[]: The string buffer
 * RETURNS: Nothing.
 */
void itoa_recursive(int number, char string[]);

int main(void) {
    char str[MAXLEN];

    itoa_recursive(23443, str);
    assert(strcmp(str, "23443") == 0);
    itoa_recursive(-23443, str);
    assert(strcmp(str, "-23443") == 0);
    itoa_recursive(INT_MAX, str);
    assert(strcmp(str, "2147483647") == 0);
    itoa_recursive(INT_MIN, str);
    assert(strcmp(str, "-2147483648") == 0);

    return 0;
}

void itoa_recursive(int n, char s[]) {
    static int i;

    if (n / 10 == 0) {
        i = 0;
        if (n < 0)
            s[i++] = '-';
        s[i++] = ((n < 0) ? -(n % 10) : n % 10) + '0';
        s[i] = '\0';
        return;
    }
    itoa_recursive(n / 10, s);
    s[i++] = ((n < 0) ? -(n % 10) : n % 10) + '0';
    s[i] = '\0';
}
