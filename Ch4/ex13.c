/*
 * Program to convert integer to string using recursive function.
 */

#include <assert.h>
#include <string.h>

#define MAXLEN 1000

/*
 * NAME: reverse_recursive
 * PURPOSE: To reverse the given string
 * PARAMETERS:
 *      - char string[]: The string to reverse
 *      - int start: The start index of string
 *      - int count: The number of characters to reverse
 * RETURNS: Nothing
 * SIDE EFFECTS: Changes the original parameter to get reverse
 */
void reverse_recursive(char string[], int start, int count);

int main(void) {
    char str[MAXLEN];

    strcpy(str, "Apple! It is a trillion $ company.\n");
    reverse_recursive(str, 0, strlen(str));
    assert(strcmp(str, "\n.ynapmoc $ noillirt a si tI !elppA") == 0);
    strcpy(str, "MangoSoft");
    reverse_recursive(str, 0, strlen(str));
    assert(strcmp(str, "MangoSoft") != 0);

    return 0;
}

void reverse_recursive(char s[], int start, int n) {
    char c;

    if (start >= start + n - 1)
        return;

    c = s[start];
    s[start] = s[start + n - 1];
    s[start + n - 1] = c;
    reverse_recursive(s, start + 1, n - 2);
}
