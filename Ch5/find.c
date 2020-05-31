/*
 * Program to search a substring pattern within a string.
 */

#include <stdio.h>
#include <string.h>

#include "../include/strutils.h"

#define MAXLEN 1000

int main(int argc, char *argv[]) {
    char line[MAXLEN];
    long linenum = 0;
    int found = 0, number = 0, except = 0;

    /* Process optional arguments */
    while (--argc > 0 && (*++argv)[0] == '-') {
        char c;
        while ((c = *++argv[0]))
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: invalid option '-%c'\n", c);
                argc = 0;
                break;
            }
    }
    if (argc != 1)
        printf("Usage: find [options] pattern\n");
    else
        while (get_line(line, MAXLEN) > 0) {
            linenum++;
            if ((strstr(line, argv[0]) != NULL) != except) {
                if (number)
                    printf("%ld: ", linenum);
                printf("%s", line);
                found++;
            }
        }

    if (found)
        return 0;
    else
        return 1;
}
