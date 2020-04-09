#include <stdio.h>
#include <stdlib.h>

#include "include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: detab
 * PURPOSE: To replace each tab character with 'n' spaces
 * RETURNS: Nothing
 */
void detab(char line[], int length, int tabstop, int max_limit);

/*
 * NAME: entab
 * PURPOSE: To replace 'n' spaces with a tab character
 * RETURNS: Nothing
 */
void entab(char line[], int length, int tabstop);

int main(void) {
    int ts = 4, len;
    char line[MAXLEN];

    while ((len = get_line(line, MAXLEN)) > 0) {
        entab(line, len, ts);
        printf("%s", line);
    }

    return 0;
}

void detab(char s[], int n, int ts, int lim) {
    for (int i = 0; i < n; ++i)
        if (s[i] == '\t') {
            // Replacing 1 tab with 'ts' spaces
            // increases the length of the string
            n += ts - 1;
            // Check for overflow condition
            if (n >= lim) {
                fprintf(stderr, "Error! Input exceeds buffer size.\n");
                exit(EXIT_FAILURE);
            }

            // Terminate the string at new length
            s[n] = '\0';
            // Shift all characters from the last to before the tab char
            // by 'n - ts' places to the right
            for (int j = n - ts; j > i; --j) s[j + ts - 1] = s[j];
            // Then, insert 'ts' number of spaces instead of the tab
            for (int j = i; j < i + ts; ++j) s[j] = ' ';
        }
}

void entab(char s[], int n, int ts) {
    int index;

    for (int i = 0, nspace = 0; i < n; ++i, nspace = 0) {
        // Whenever a space char is found, increase contd. space counter.
        // Then check to see if any more space characters exist.
        if (s[i] == ' ') {
            ++nspace;
            // Here, we group a continuous string of spaces (if it exists)
            // into chunks, each of which is at most 'ts' spaces wide.
            for (index = i + 1; index < n && nspace < ts && s[index] == ' ';
                 ++index)
                // Increase the continuous space counter if more spaces
                // are found immediately after the last space.
                ++nspace;
            if (nspace == ts) {
                // If 'ts' continuous spaces are found,
                // shift each char by 'ts - 1' places to the left.
                for (int j = index; j < n; ++j) s[j - ts + 1] = s[j];
                s[i] = '\t';
                // Reduce string length and terminate the new string
                n -= ts - 1;
                s[n] = '\0';
            }
        }
    }
}
