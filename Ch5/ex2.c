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
 * NAME: getfloat
 * PURPOSE: To get a new floating point constant from the input stream.
 * PARAMETERS:
 *  - double *pfloat: The pointer to an double in which it sores the integer
 * RETURNS: The last character read, including EOF.
 * SIDE EFFECTS: Changes the parameter passed to it.
 */
int getfloat(double *pfloat);

int main(void) {
    int i, j, status;
    double numbers[SIZE];

    for (i = 0;
         i < SIZE && (status = getfloat(&numbers[i])) != EOF && status != 0;
         i++)
        ;
    for (j = 0; j < i; j++)
        printf("%s%g%s", (j > 0) ? ", " : "", numbers[j],
               (j == i - 1) ? "\n" : "");

    return 0;
}

#include <ctype.h>

int getfloat(double *pf) {
    int c;
    double sign, power;

    /* Skip white spaces */
    while (isspace(c = getchar()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        /* Put back a character if it is not a number */
        ungetc(c, stdin);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int s = c;

        if (!isdigit(c = getchar())) {
            /* Put back the '+' or '-' if not followed by a digit */
            ungetc(c, stdin);
            ungetc(s, stdin);
            return 0;
        }
    }
    /* Process integer part */
    for (*pf = 0.0; isdigit(c); c = getchar())
        *pf = *pf * 10.0 + (c - '0');
    /* Skip the '.' */
    if (c == '.')
        c = getchar();
    /* Process fractional part */
    for (power = 1.0; isdigit(c); c = getchar()) {
        *pf = *pf * 10 + (c - '0');
        power *= 10;
    }
    *pf = *pf * sign / power;
    if (c != EOF)
        ungetc(c, stdin);

    return c;
}
