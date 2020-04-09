#include <stdio.h>

#define INSIDE_WORD 1
#define OUTSIDE_WORD 0

int main(void) {
    int c, nl = 0, nw = 0, nc = 0, state = OUTSIDE_WORD;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') ++nl;
        if (c == ' ' || c == '\t' || c == '\n')
            state = OUTSIDE_WORD;
        else if (state == OUTSIDE_WORD) {
            state = INSIDE_WORD;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}
