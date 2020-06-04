/*
 * Program to convert a valid C program to words
 * readable from left-to-right.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000];          /* output string */

int main(void) {
    while (gettoken() != EOF) {  /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';
        dcl(); /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("\t%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

/*
 * NAME: dcl
 * PURPOSE: To parse a declaration in valid C.
 * PARAMETERS: None
 * RETURNS: Nothing.
 * SIDE EFFECTS: Modifies global variable 'out'.
 */
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/*
 * NAME: dirdcl
 * PURPOSE: To parse a direct-declaration in valid C.
 * PARAMETERS: None
 * RETURNS: Nothing.
 * SIDE EFFECTS: Modifies following global variables:
 *      - name
 *      - out
 */
void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl), %c\n", tokentype);
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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
