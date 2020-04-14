/*
 * Count digits, whitespace and others
 */

#include <stdio.h>

int main(void) {
    int c;
    int nwhite = 0, nother = 0, ndigits[10] = {0};

    while ((c = getchar()) != EOF) {
        switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ++ndigits[c - '0'];
                break;
            case ' ':
            case '\t':
            case '\n':
                ++nwhite;
                break;
            default:
                ++nother;
                break;
        }
    }

    printf("digits =");
    for (int i = 0; i < 10; i++) printf(" %d", ndigits[i]);
    printf(", whitespaces = %d, others = %d\n", nwhite, nother);

    return 0;
}
