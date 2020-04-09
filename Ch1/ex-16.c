/*
 * Print length and text of arbitrary length lines
 */

#include <stdio.h>

#define MAXLEN 1000

int get_line(char line[], int maxlen);
void copy(char to[], char from[]);

int main(void) {
    int len;
    char line[MAXLEN];

    while ((len = get_line(line, MAXLEN)) > 0) {
        printf("%s", line);
        if (len == MAXLEN - 1) {
            for (int c; (c = getchar()) != EOF && c != '\n'; len++) putchar(c);
            putchar('\n');
        }
        printf("%d\n\n", len);
    }

    return 0;
}

/*
 * NAME: get_line
 * RETURNS: Length of the input line
 */
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

void copy(char to[], char from[]) {
    for (int i = 0; (to[i] = from[i]) != '\0'; i++)
        ;
}
