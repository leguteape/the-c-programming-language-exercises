/*
 * Program to convert newlines and tabs to
 * visible characters, and vise versa.
 */

#include <stdio.h>

#include "include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: escape
 * PURPOSE: Convert newlines and tabs to visible characters.
 * PARAMETERS:
 *  - char target[]: The target string
 *  - char source[]: The source string
 *  - int max_length: The maximum possible length of strings
 * RETURNS: Nothing.
 */
void escape(char target[], char source[], int max_length);

/*
 * NAME: escape
 * PURPOSE: Convert visible \n and \t to newlines and tabs.
 * PARAMETERS:
 *  - char target[]: The target string
 *  - char source[]: The source string
 *  - int max_length: The maximum possible length of strings
 * RETURNS: Nothing.
 */
void deescape(char target[], char source[], int max_length);

int main(void) {
    char source[MAXLEN], target[MAXLEN];

    while (get_line(source, MAXLEN) > 0) {
        escape(target, source, MAXLEN);
        deescape(target, source, MAXLEN);
        printf("%s", target);
    }

    return 0;
}

void escape(char t[], char s[], int lim) {
    int dest = 0;

    for (int i = 0; dest + 1 < lim - 1 && s[i] != '\0'; i++) {
        switch (s[i]) {
            case '\n':
                t[dest++] = '\\';
                t[dest++] = 'n';
                break;
            case '\t':
                t[dest++] = '\\';
                t[dest++] = 't';
                break;
            default:
                t[dest++] = s[i];
                break;
        }
    }
    t[dest] = '\0';
}

void deescape(char t[], char s[], int lim) {
    int dest = 0;

    for (int i = 0; i + 1 < lim - 1 && s[i] != '\0'; i++) {
        switch (s[i]) {
            case '\\':
                switch (s[i + 1]) {
                    case 'n':
                        t[dest++] = '\n';
                        break;
                    case 't':
                        t[dest++] = '\t';
                        break;
                }
                break;
            default:
                t[dest++] = s[i];
                break;
        }
    }
    t[dest] = '\0';
}
