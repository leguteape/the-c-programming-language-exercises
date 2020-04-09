#include <stdio.h>

int main(void) {
    int c, nw = 0;

    while ((c = getchar()) != EOF)
        if (c == '\n' || c == '\t' || c == ' ') ++nw;
    printf("%d\n", nw);

    return 0;
}
