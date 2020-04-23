/*
 * Program to search a substring pattern within a string.
 */

#include <stdio.h>

#include "../include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: strindex
 * PURPOSE: Search for a substring withing the given string.
 * PARAMETERS:
 *  - char string[]: The string to search in
 *  - char pattern[]: The pattern to find
 * RETURNS: The index of the first character of the first match,
 *          -1 if no match is found.
 */
int strindex(char string[], char pattern[]);

int main(void) {
    char pattern[] = "ould";
    char line[MAXLEN];
    int found = 0;

    while (get_line(line, MAXLEN) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }

    if (found)
        return 0;
    else
        return 1;
}

int strindex(char s[], char p[]) {
    int i;

    for (i = 0; s[i] != '\0'; i++) {
        int j, k;

        for (j = i, k = 0; p[j] != '\0' && s[j] == p[k]; j++, k++)
            ;
        if (k > 0 && p[k] == '\0')
            return i;
    }

    return -1;
}
