/*
 * Program to display the last 'n' lines of an input.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/strutils.h"

#define MAXLINES 5000
#define MAXLEN 1000
#define DEFAULT_N 10

int main(int argc, char *argv[]) {
    char *linetab[MAXLINES];
    char line[MAXLEN];
    int n = 0, nlines, len, i;
    char *p;

    while (--argc > 0 && *(argv + 1) && (*++argv)[0] == '-') {
        char c;

        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                if (!isdigit(c = *++argv[0])) {
                    /* Restore the last read character of current argument
                     * if not a digit */
                    --argv[0];
                    if (*(argv + 1) == NULL || !isdigit(c = *(argv + 1)[0])) {
                        fprintf(stderr,
                                "tail: invalid option usage '-n LINES'\n");
                        break;
                    }
                    /* If next argument begins with a digit, go there */
                    argc--, argv++;
                }
                n = c - '0';
                while (isdigit(c = *++argv[0]))
                    n = n * 10 + c - '0';
                if (!c)
                    /* If the last read character is a '\0',
                     * restore it */
                    --argv[0];
                break;
            default:
                fprintf(stderr, "tail: invalid option '%c'\n", c);
                return 1;
            }
        }
    }
    if (argc != 0) {
        fprintf(stderr, "Usage: tail [OPTIONS]\n");
        return 2;
    }
    if (n == 0)
        n = DEFAULT_N;

    for (nlines = 0; nlines < MAXLINES && (len = get_line(line, MAXLEN)) > 0;
         nlines++) {
        p = malloc(len + 1);
        strcpy(p, line);
        linetab[nlines] = p;
    }
    for (i = nlines - n; i < nlines; i++)
        printf("%s", linetab[i]);
    for (i = 0; i < nlines; i++)
        free(linetab[i]);

    return 0;
}
