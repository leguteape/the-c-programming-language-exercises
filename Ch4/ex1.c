/*
 * Program to search a substring pattern within a string.
 */

#include <assert.h>
#include <string.h>

#include "../include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: strindex
 * PURPOSE: Search for a substring withing the given string
 *          from the back.
 * PARAMETERS:
 *  - char string[]: The string to search in
 *  - char pattern[]: The pattern to find
 * RETURNS: The index of the first character of the last match,
 *          -1 if no match is found.
 */
int strrindex(const char string[], const char pattern[]);

int main(void) {
    assert(strrindex("This is a string.", "string") == 10);
    assert(strrindex("An Apple of the Apple's eye", "Apple") == 16);
    assert(strrindex("", "Apple") == -1);
    assert(strrindex("An Apple of the eye", "") == -1);
    assert(strrindex("An Apple of the eye", "Microsoft") == -1);

    return 0;
}

int strrindex(const char s[], const char p[]) {
    int i;

    for (i = strlen(s) - 1; i >= 0; i--) {
        int j = i, k = strlen(p) - 1;

        // Empty pattern string
        if (k < 0)
            return -1;
        while (k >= 0 && s[j] == p[k])
            j--, k--;
        if (k < 0)
            return j + 1;
    }

    return -1;
}
