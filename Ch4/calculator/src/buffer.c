/* buffer.c */

#include "calc.h"
#include <stdio.h>

#define BUFSIZE 100

/* Push back implementation for 'getch' and 'ungetch' */
static char pushed_char;
static boolean pushback = FALSE;

/* Push back implementation for 'ungets' */
static char buffer[BUFSIZE];
static int bufp = 0;

int getch(void) {
    if (pushback) {
        pushback = FALSE;
        return pushed_char;
    }
    return getchar();
}

void ungetch(int ch) {
    if (pushback)
        printf("ungetch: error: Buffer overflow\n");
    else {
        pushback = TRUE;
        pushed_char = ch;
    }
}

void ungets(char s[]) {
    int i;

    for (i = 0; s[i] != '\n' && s[i] != '\0'; i++)
        if (bufp >= BUFSIZE) {
            printf("ungets: error: Buffer overflow\n");
            break;
        } else
            buffer[bufp++] = s[i];
}
