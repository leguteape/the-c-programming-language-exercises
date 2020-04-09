#include <stdio.h>

int main(void) {
    long nl = 0;
    int c;

    while ((c = getchar()) != EOF)
        if (c == '\n') ++nl;
    printf("%ld\n", nl);

    return 0;
}
