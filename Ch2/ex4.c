/*
 * Program to squeeze a string, i.e. remove all characters
 * of string that match a character of another string.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
 * NAME: squeeze
 * PURPOSE: Function to  remove all characters of
 *          string that match a character of another string
 * PARAMETERS:
 *      - char to_squeeze[]: The string from which to remove characters
 *      - char chars_to_remove[]: The characters which are to be removed
 * RETURNS: Nothing
 */
void squeeze(char to_squeeze[], char chars_to_remove[]);

int main(void) {
    char str1[] = "avacado", str2[] = "ao";

    squeeze(str1, str2);
    assert(strcmp(str1, "vcd") == 0);

    return 0;
}

void squeeze(char s1[], char s2[]) {
    for (int j = 0; s2[j] != 0; ++j) {
        int di = 0;

        for (int si = 0; s1[si] != '\0'; ++si)
            if (s1[si] != s2[j]) s1[di++] = s1[si];
        s1[di] = '\0';
    }
}
