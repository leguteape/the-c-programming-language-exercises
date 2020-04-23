/*
 * Program to swap two numbers using a macro.
 */

#include <stdio.h>

#define PRINT_INTS(x, y) printf("%d %d\n", x, y)

#define SWAP(t, x, y)                                                          \
    do {                                                                       \
        t temp = x;                                                            \
        x = y;                                                                 \
        y = temp;                                                              \
    } while (0)

int main(void) {
    int x = 1, y = 2;

    PRINT_INTS(x, y);
    SWAP(int, x, y);
    PRINT_INTS(x, y);

    return 0;
}
