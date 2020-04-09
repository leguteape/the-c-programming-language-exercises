/*
 * Count digits, whitespace and others
 */

#include <stdio.h>

int main(void) {
    int c;
    int nwhite = 0, nother = 0, ndigits[10] = {0};

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigits[c - '0'];
        else if (c == ' ' || c == '\t' || c == '\n')
            ++nwhite;
        else
            ++nother;

    printf("digits =");
    for (int i = 0; i < 10; i++) printf(" %d", ndigits[i]);
    printf(", whitespaces = %d, others = %d\n", nwhite, nother);

    return 0;
}
