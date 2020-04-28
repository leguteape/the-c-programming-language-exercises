/*
 * Program to implement a function that gets an integer from stdin.
 * The program communicates the integer value using a pointer
 * to an integer sent by caller.
 * The end of the input stream is indicated by the EOF value
 * that it returns.
 */

#include <stdio.h>

#define SIZE 10

/*
 * NAME: getint
 * PURPOSE: To get a new integer constant from the input stream.
 * PARAMETERS:
 *  - int *pinteger: The pointer to an int in which it sores the integer
 * RETURNS: The last character read, including EOF.
 * SIDE EFFECTS: Changes the parameter passed to it.
 */
int getint(int *pinteger);

int main(void) {
    int i, j, status;
    int numbers[SIZE];

    for (i = 0;
         i < SIZE && (status = getint(&numbers[i])) != EOF && status != 0; i++)
        ;
    for (j = 0; j < i; j++)
        printf("%s%d%s", (j > 0) ? ", " : "", numbers[j],
               (j == i - 1) ? "\n" : "");

    return 0;
}

#include <ctype.h>

int getint(int *pi) {
    int c, sign;

    while (isspace(c = getchar()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetc(c, stdin);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int s = c;

        if (!isdigit(c = getchar())) {
            ungetc(c, stdin);
            ungetc(s, stdin);
            return 0;
        }
    }
    for (*pi = 0; isdigit(c); c = getchar())
        *pi = *pi * 10 + (c - '0');
    *pi *= sign;
    if (c != EOF)
        ungetc(c, stdin);

    return c;
}
