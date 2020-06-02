#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/strutils.h"

#define MAXLEN 1000
#define MAX_TABSTOPS 100
#define DEFAULT_TABSTOP 4

/* enum to represent the boolean type */
typedef enum boolean { FALSE, TRUE } Boolean;

void entab(char line[], int length, int tabstops[], int tabslen);

int main(int argc, char *argv[]) {
    char line[MAXLEN];
    int len;
    int tabstops[MAX_TABSTOPS], ntabs = 0;
    Boolean is_ascending(int tabstops[], int ntabs);

    while (--argc > 0 && *(argv + 1) != NULL && (*++argv)[0] == '-') {
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
        entab(line, len, tabstops, ntabs);
        printf("%s", line);
    }

    return 0;
}

/*
 * NAME: entab
 * PURPOSE: To replace 'n' spaces with a tab character
 * RETURNS: Nothing
 */
void entab(char s[], int n, int ts[], int tslen) {
    int i, j, tabi;
    int nspace;
    Boolean done = FALSE;
    int tabstop = 0; /* To keep track of the current tab stop value */

    for (i = 0, nspace = 0, tabi = 0; !done && i < n; ++i) {
        /* Whenever a space char is found, increase contd space counter.
         * Then check to see if any more space characters exist */
        if (s[i] != ' ') {
            if (tslen > 1)
                break;
            else
                continue;
        }

        ++nspace;

        if (tslen > 1)
            tabstop = ts[tabi];
        else
            tabstop += ts[tabi];
        /* Here, we group a continuous string of spaces (if it exists),
         * into chunks, each of which is at most 'ts' spaces wide */
        for (j = i + 1; j < n && nspace < tabstop && s[j] == ' '; ++j)
            /* Increase the continuous space counter if more spaces
             * are found immediately after the last space */
            ++nspace;
        if (tslen > 1 && s[j] != ' ')
            done = TRUE;
        if (nspace == tabstop) {
            int k;

            /* If 'ts' continuous spaces are found,
             * shift each char by 'ts - 1' places to the left */
            for (k = j; k < n; ++k)
                if (tabi > 0)
                    s[k - ts[tabi] + ts[tabi - 1] + 1] = s[k];
                else
                    s[k - ts[tabi] + 1] = s[k];
            s[i] = '\t';
            if (tabi > 0)
                /* Reduce string length and terminate the new string */
                n -= ts[tabi] - ts[tabi - 1] - 1;
            else
                /* Reduce string length and terminate the new string */
                n -= ts[tabi] - 1;
        }
        s[n] = '\0';

        if (tslen != 1) {
            if (tabi == tslen - 1)
                done = TRUE;
            else
                tabi++;
        }
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
