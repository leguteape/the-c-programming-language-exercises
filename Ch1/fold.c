/*
 * PURPOSE: Program to "fold" or "soft-wrap" long lines of text
 * into two or more shorter linesafter the last non-blank character
 * that occours before the nthcolumn of input
 */

#include <stdio.h>

#include "include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: fold
 * PURPOSE: To "fold" or "wrap" a long line into two or more
 *          shorter lines of input by breaking after the last
 *          non-blank char before "fold_column".
 * PARAMETERS:
 *      - char line[]: The string to fold
 *      - int fold_column: The point before which to fold
 * RETURNS: Nothing
 */
void fold(const char line[], int fold_column);

int main(void) {
    char line[MAXLEN];

    while (get_line(line, MAXLEN) > 0) fold(line, 80);

    return 0;
}

void fold(const char s[], int n) {
    int len = length(s);

    // If the line is less than n characters wide,
    // just print it and return, no need to fold
    if (len < n) {
        printf("%s", s);
        return;
    }

    int wrap_at = 0;  // This is the point at which to wrap
    // Basically, we want to keep wrapping until the remaining
    // text in the line is too short to wrap
    for (int i = 0, cur = 0; len - wrap_at >= n; ++i) {
        cur = wrap_at;
        // Find the point at which to wrap. This is donw by searching
        // backwards from the intended point of wrap (cur + n) to the
        // point of the cursor (cur).
        for (int j = cur + n; j >= cur; --j)
            // This test makes sure that we wrap after the last non-space
            // character before the fold point.
            if ((s[j] == ' ' || s[j] == '\t') &&
                (s[j - 1] != ' ' || s[j - 1] != '\t')) {
                wrap_at = j;
                break;
            }
        // If no space was found anywhere between the fold point and
        // the last fold, fold exactly at the fold point.
        if (wrap_at == cur) wrap_at = cur + n;

        // Print the characters between the last fold point and
        // current fold point and display a '\n' at the end
        for (int i = cur; i < wrap_at; ++i) putchar(s[i]);
        putchar('\n');
    }
    // Print out the remaining text (which was too short to fold)
    // till the end
    for (int i = wrap_at; i < len; ++i) putchar(s[i]);
}
