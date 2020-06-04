/*
 * Program to convert a word description of a C
 * declaration into valid C syntax.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void undcl(void);

int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000];          /* output string */

int main(void) {
    int c, type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                while ((c = getc(stdin)) == ' ' || c == '\t')
                    ;
                ungetc(c, stdin);
                if (c == '(' || c == '[')
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("error: invalid input at %s\n", token);
        }
        printf("%s\n", out);
    }

    return 0;
}

/*
 * NAME: gettoken
 * PURPOSE: To identify and isolate the next token.
 * PARAMETERS: None
 * RETURNS: The type of the token just processed.
 * SIDE EFFECTS: Modifies following global variables:
 *      - token
 *      - tokentype
 */
int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getc(stdin)) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getc(stdin)) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getc(stdin)) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getc(stdin));)
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    } else
        return tokentype = c;
}
