/*
 * Program to reverse its input one line at a time
 */

#include <stdio.h>

#include "include/strutils.h"

#define MAXLEN 1000

int main(void) {
    char line[MAXLEN];

    while (get_line(line, MAXLEN) > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}
