/*
 * Print a histogram of the lengths of words in the input
 */

#include <stdio.h>

#define INSIDE_WORD 1
#define OUTSIDE_WORD 0

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            putchar('\n');
            while ((c = getchar()) == ' ' || c == '\t' || c == '\n')
                ;
            if (c != EOF) putchar('#');
        } else
            putchar('#');
    }

    return 0;
}
