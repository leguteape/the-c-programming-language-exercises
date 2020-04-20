/* token.c */

#include "buffer.h"
#include "calc.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_function(char s[]) {
    int c, i;

    i = 0;
    if (isalpha(s[0] = c = getch()))
        while (isalpha(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    for (i = 0; s[i] != '\0'; i++)
        if (i - 2 >= 0 && s[i - 2] == 's' && s[i - 1] == 'i' && s[i] == 'n')
            return SIN_FOUND;
        else if (i - 2 >= 0 && s[i - 2] == 'c' && s[i - 1] == 'o' &&
                 s[i] == 's')
            return COS_FOUND;
        else if (i - 2 >= 0 && s[i - 2] == 'e' && s[i - 1] == 'x' &&
                 s[i] == 'p')
            return EXP_FOUND;
    return NO_FUNC_FOUND;
}

void get_operand(char s[], int i) {
    int c;

    while (isdigit(s[++i] = c = getch()))
        ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    /* Pur back the extra character read to determine end of an operand */
    if (c != EOF)
        ungetch(c);
}

int get_var_name(char s[]) {
    int c;
    int i = 0;

    while (isalpha(s[i++] = c = getch()))
        ;
    s[i - 1] = '\0';
    ungetch(c);

    if (i - 1 == 1)
        return VAR_EXPAND_FOUND;
    else if (strcmp(s, "ans") == 0)
        return ANS_EXPAND_FOUND;
    else {
        for (i = 0; s[i] != '\0'; i++)
            ungetch(s[i]);
        printf("%s\n", s);
        return INVALID_VAR_USAGE;
    }
}

int get_token(char s[]) {
    int c, i;

    /* Skip whitespace */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0'; /* Defence for the early return on finding operator */
    i = 0;
    /* Check for operator */
    if (!isdigit(c) && c != '.') {
        if (c == '$') {
            /* '$' is used for variable expansion (like in the shell) */
            if (isalpha(s[++i] = c = getch())) {
                /* Put back the last character and return */
                ungetch(c);
                return get_var_name(s);
            } else {
                /* Handle missing variable name error during expansion */
                s[i] = '\0'; /* Terminate the string buffer */
                /* Put back the last character and return */
                ungetch(c);
                return INVALID_VAR_USAGE;
            }
        } else if (isalpha(c)) {
            int ftype;

            ungetch(c);
            if ((ftype = get_function(s)) != NO_FUNC_FOUND)
                return ftype;
            /* Handle errors related to invalid variable use */
            while (isalnum(c = getch()) || c == ' ' || c == '\t')
                if ((c = getch()) != '=') {
                    /* If first non-whitespace token is not '=', error */
                    ungetch(c);
                    return INVALID_VAR_USAGE;
                } else {
                    /* A single letter variable is found */
                    ungetch(c);
                    return VAR_ASSIGN_FOUND;
                }
        } else if (c != '-')
            /* Handle negative numbers */
            return c;
        else if (c == '-' && !isdigit(s[++i] = c = getch())) {
            /* Terminate the string buffer */
            s[i] = '\0';
            /* Push the extra character back */
            if (c != EOF)
                ungetch(c);
            /* Return the '-' operator */
            return s[i - 1];
        }
    }
    /* Put the number (possibly fractional) into the buffer */
    if (isdigit(c))
        get_operand(s, i);

    return NUMBER_FOUND;
}
