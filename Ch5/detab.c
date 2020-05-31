#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/strutils.h"

#define MAXLEN 1000
#define MAX_TABSTOPS 100
#define DEFAULT_TABSTOP 4

/* enum to represent the boolean type */
typedef enum boolean { FALSE, TRUE } Boolean;

void detab(char line[], int length, int tabstops[], int tabslen, int max_limit);

int main(int argc, char *argv[]) {
    char line[MAXLEN];
    int len;
    int tabstops[MAX_TABSTOPS], ntabs = 0;
    Boolean is_ascending(int tabstops[], int ntabs);

    while (--argc > 0 && *(argv + 1) && (*++argv)[0] == '-') {
        int c, ts;

        while ((c = *++argv[0])) {
            switch (c) {
            case 't':
                if (!isdigit(c = *++argv[0])) {
                    /* Restore the last read character of current argument
                     * if not a digit */
                    --argv[0];
                    if (*(argv + 1) == NULL || !isdigit(c = *(argv + 1)[0])) {
                        fprintf(stderr,
                                "entab: invalid option usage '-t LIST'\n");
                        break;
                    }
                    /* If next argument begins with a digit, go there */
                    argc--, argv++;
                }
                ts = c - '0';
                while (isdigit(c = *++argv[0]) || c == ',') {
                    if (c == ',') {
                        tabstops[ntabs++] = ts;
                        ts = 0;
                    } else
                        ts = ts * 10 + (c - '0');
                }
                tabstops[ntabs++] = ts;

                if (!is_ascending(tabstops, ntabs)) {
                    fprintf(stderr, "entab: tab sizes must be ascending\n");
                    return 2;
                }

                if (!c)
                    /* If the last read character is a '\0',
                     * restore it */
                    --argv[0];
                break;
            default:
                argc = 1;
                fprintf(stderr, "entab: invalid option '-%c'\n", c);
                break;
            }
        }
    }

    if (argc != 0) {
        fprintf(stderr, "Usage: entab [options]\n");
        return 1;
    }

    if (ntabs == 0)
        tabstops[ntabs++] = DEFAULT_TABSTOP;

    while ((len = get_line(line, MAXLEN)) > 0) {
        detab(line, len, tabstops, ntabs, MAXLEN);
        printf("%s", line);
    }

    return 0;
}

/*
 * NAME: detab
 * PURPOSE: To replace each tab character with 'n' spaces
 * RETURNS: Nothing
 */
void detab(char s[], int n, int ts[], int tslen, int lim) {
    int i, ntabs;

    for (i = 0, ntabs = 0; i < n; ++i)
        if (s[i] == '\t') {
            if (ntabs < tslen) {
                int k;

                /* Replacing 1 tab with 'ts' spaces */
                /* increases the length of the string */
                n += ts[ntabs] - 1;
                /* Check for overflow condition */
                if (n >= lim) {
                    fprintf(stderr, "Error! Input exceeds buffer size.\n");
                    exit(EXIT_FAILURE);
                }

                /* Terminate the string at new length */
                s[n] = '\0';
                /* Shift all characters from the last to before the tab char */
                /* by 'n - ts' places to the right */
                for (k = n - ts[ntabs]; k > i; --k)
                    s[k + ts[ntabs] - 1] = s[k];
                /* Then, insert 'ts' number of spaces instead of the tab */
                for (k = i; k < i + ts[ntabs]; ++k)
                    s[k] = ' ';
                /* To take into account the single tabstop situation */
                ntabs = (tslen == 1) ? 0 : ntabs + 1;
            } else
                s[i] = ' ';
        }
}

/*
 * NAME: is_ascending
 * PURPOSE: To check if items in an array are ascending or not.
 * PARAMETERS:
 *  - int a[]: The array of items
 *  - int len: The size of the array
 * RETURNS: 1 if items are in ascending order,
 *          0 otherwise.
 */
Boolean is_ascending(int a[], int len) {
    int i, j;

    for (i = 0; i < len; i++)
        for (j = i + 1; j < len; j++)
            if (a[i] > a[j])
                return FALSE;
    return TRUE;
}
