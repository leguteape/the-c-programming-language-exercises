/*
 * Print a histogram of the frequencies of different characters of input
 */

#include <stdio.h>

int main(void) {
    int c;
    int nwhite = 0;
    int ndigits[10] = {0}, nlower[26] = {0}, nupper[26] = {0};

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigits[c - '0'];
        else if (c == ' ' || c == '\t' || c == '\n')
            ++nwhite;
        else if (c >= 'a' && c <= 'z')
            ++nlower[c - 'a'];
        else if (c >= 'A' && c <= 'Z')
            ++nupper[c - 'A'];

    printf("Digits:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d:\t", i);
        for (int j = 0; j < ndigits[i]; j++) putchar('#');
        putchar('\n');
    }
    printf("\nLowercase:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c:\t", i + 'a');
        for (int j = 0; j < nlower[i]; j++) putchar('#');
        putchar('\n');
    }
    printf("\nUppercase:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c:\t", i + 'A');
        for (int j = 0; j < nupper[i]; j++) putchar('#');
        putchar('\n');
    }
    printf("\nWhitespace:\n");
    for (int i = 0; i < nwhite; i++) putchar('#');
    putchar('\n');

    return 0;
}
