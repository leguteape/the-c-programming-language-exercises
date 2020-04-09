/*
 * Program that prints its input one word per line
 */

#include <stdio.h>

#define INSIDE_WORD 1
#define OUTSIDE_WORD 0

int main(void) {
    int c, state = OUTSIDE_WORD;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == INSIDE_WORD) putchar('\n');
            state = OUTSIDE_WORD;
        } else if (state == OUTSIDE_WORD) {
            state = INSIDE_WORD;
            putchar(c);
        } else
            putchar(c);
    }

    return 0;
}
