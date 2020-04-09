/*
 * Program to remove trailing blanks and tabs from each line of input.
 * Also delete entirely blank lines.
 */

#include <stdio.h>

#define MAXLEN 1000

/*
 * NAME: get_line
 * RETURNS: Length of the input line
 */
int get_line(char line[], int maxlen);

/*
 * NAME trim
 * PURPOSE: To trim out trailing blanks and tabs and also remove blank lines.
 * RETURNS: Nothing
 */
char *trim(char *line);

/*
 * NAME: length
 * RETURNS: Length of the given string
 */
int length(const char *line);

int main(void) {
    char line[MAXLEN];
    char *trimmed = NULL;

    while (get_line(line, MAXLEN) > 0)
        if ((trimmed = trim(line)) != NULL) printf("%s", trimmed);
    putchar('\n');

    return 0;
}

char *trim(char *s) {
    int len = length(s);

    // If string is empty, i.e. contains only a '\n'
    if (len <= 1) return NULL;

    int curr = len - 1;
    // If the current line has '\n', '\t' or ' ' at the end, keep reducing the
    // counter
    while (curr >= 0 && (s[curr] == '\n' || s[curr] == '\t' || s[curr] == ' '))
        --curr;
    // Here len - 1 is used to account for the '\n' at the end
    if (curr < len - 1) {
        s[curr + 1] = '\n';
        s[curr + 2] = '\0';
    }

    return s;
}

int get_line(char s[], int lim) {
    int len, c;

    for (len = 0; len < lim - 1 && (c = getchar()) != EOF && c != '\n'; len++)
        s[len] = c;
    if (c == '\n') {
        s[len] = c;
        ++len;
    }
    s[len] = '\0';

    return len;
}

int length(const char *s) {
    int len = 0;

    while (*s++ != '\0') ++len;

    return len;
}
