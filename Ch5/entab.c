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
    int i, j, index;
    int nspace;
    Boolean done = FALSE;

    for (i = 0, nspace = 0; !done && i < n; ++i) {
        /* Whenever a space char is found, increase contd space counter.
         * Then check to see if any more space characters exist */
        if (s[i] != ' ')
            break;

        ++nspace;
        /* Here, we group a continuous string of spaces (if it exists),
         * into chunks, each of which is at most 'ts' spaces wide */
        for (j = 0; !done && j < tslen; j++) {
            for (index = i + 1; index < n && nspace < ts[j] && s[index] == ' ';
                 ++index)
                /* Increase the continuous space counter if more spaces
                 * are found immediately after the last space */
                ++nspace;
            if (s[index] != ' ')
                done = TRUE;
            if (nspace == ts[j]) {
                int k;

                /* If 'ts' continuous spaces are found,
                 * shift each char by 'ts - 1' places to the left */
                for (k = index; k < n; ++k)
                    if (j > 0)
                        s[k - ts[j] + ts[j - 1] + 1] = s[k];
                    else
                        s[k - ts[j] + 1] = s[k];
                if (j > 0) {
                    s[++i] = '\t';
                    /* Reduce string length and terminate the new string */
                    n -= ts[j] - ts[j - 1] - 1;
                } else {
                    s[i] = '\t';
                    /* Reduce string length and terminate the new string */
                    n -= ts[j] - 1;
                }
                s[n] = '\0';
                if (j == tslen - 1)
                    done = TRUE;
            }
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
