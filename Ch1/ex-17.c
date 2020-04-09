/*
 * Print all lines that are longer than 80 characters
 */

#include <stdio.h>

#define CHAR_LIMIT 80
#define MAXLEN 1000

/*
 * NAME: get_line
 * RETURNS: Length of the input line
 */
int get_line(char s[], int lim);

int main(void) {
    int len;
    char line[MAXLEN];

    while ((len = get_line(line, MAXLEN)) > 0)
        if (len > CHAR_LIMIT) printf("%s\n", line);

    return 0;
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
