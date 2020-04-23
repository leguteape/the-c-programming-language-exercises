/*
 * Program to convert a string of floating point numbers to number.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define MAXLEN 100

/*
 * NAME: stringtof
 * PURPOSE: To convert a string of floating point value to number.
 * PARAMETERS:
 *  - const char string[]: The string with the number
 * RETURNS: Double precision value for the number.
 */
double stringtof(const char string[]);

int main(void) {
    printf("%f\n", stringtof("23224.523"));
    printf("%f\n", stringtof("-23224.523"));
    printf("%f\n", stringtof("23224.523E-2"));
    printf("%f\n", stringtof("23224.523E2"));
    printf("%f\n", stringtof("-23224.523e2"));
    printf("%e\n", stringtof("-23223423424.53242423e-2"));

    return 0;
}

double stringtof(const char s[]) {
    double val, power, exponent;
    int i, sign, expsign;

    /* Skip whitespace characters */
    for (i = 0; isspace(s[i]); i++)
        ;
    /* Set a sign value */
    sign = (s[i] == '-') ? -1 : 1;
    /* Skip the sign, if any */
    if (s[i] == '+' || s[i] == '-')
        i++;
    /* Conversion begins here */
    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10.0 + (s[i] - '0');
    if (s[i] == '.')
        i++;
    /* Handle the part after the decimal dot */
    for (power = 1.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
        power *= 10;
    }
    /* Handle the part after the exponent 'e' or 'E' */
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    expsign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (exponent = 0.0; isdigit(s[i]); i++)
        exponent = exponent * 10.0 + (s[i] - '0');

    return sign * val / power * pow(10, expsign * exponent);
}
