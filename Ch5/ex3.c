#include <assert.h>
#include <string.h>

#define MAXLEN 1000

/*
 * NAME: concat
 * PURPOSE: Concatenates the source string into the target string.
 * PARAMETERS:
 *  - char *target: The target string
 *  - char *source: The source string
 * RETURNS: Nothing.
 * SIDE EFFECTS: Changes the target string.
 */
void concat(char *target, char *source);

int main(void) {
    char target[MAXLEN] = "Apple";
    char *source = " Computer";

    concat(target, source);
    assert(strcmp(target, "Apple Computer") == 0);

    return 0;
}

void concat(char *t, char *s) {
    while (*t)
        t++;
    while ((*t++ = *s++))
        ;
}
