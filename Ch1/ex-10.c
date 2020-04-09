/*
 * Copy input to output replacing each tab by '\t', backspace by '\b'
 * and bsckslash by '\\'.
 */

#include <stdio.h>

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        } else if (c == '\b') {
            putchar('\\');
            putchar('b');
        } else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        } else
            putchar(c);
    }

    return 0;
}
