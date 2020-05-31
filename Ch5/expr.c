/*
 * Program to evaluate a reverse polish expression
 * given from the command line.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_OP_LEN 100
#define NUMBER_FOUND 1

int getop(char *expression, char *buffer);
void push(double item);
double pop(void);

int main(int argc, char *argv[]) {
    int type;
    double op2;
    char s[MAX_OP_LEN];

    if (argc == 1) {
        fprintf(stderr, "expr: missing operand\n");
        fprintf(stderr, "Usage: expr EXPRESSION\n");
        return -1;
    }

    while (--argc > 0 && (type = getop(*++argv, s))) {
        switch (type) {
        case NUMBER_FOUND:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 == 0.0)
                printf("error: division by zero\n");
            else
                push(pop() / op2);
            break;
        default:
            printf("error: unknown command '%s'\n", s);
            return -1;
        }
    }
    printf("%.8g\n", pop());

    return 0;
}

#define MAXVAL 100

int sp = 0; /* Next free stack position */
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
    if (sp >= MAXVAL)
        printf("error: stack full, can't push\n");
    else
        val[sp++] = f;
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp <= 0) {
        printf("error: empty stack\n");
        return 0.0;
    } else
        return val[--sp];
}

#include <ctype.h>

int getch(void);

/* getop: get next operator or numeric operand */
int getop(char *expr, char *s) {
    int c;

    if (!expr)
        return '\0';

    while ((*s = c = *expr++) == ' ' || c == '\t')
        ;
    *++s = '\0';
    /* Not a number */
    if (!isdigit(c) && c != '.')
        return c;
    /* Collect integer part */
    if (isdigit(c))
        while (isdigit(*s++ = c = *expr++))
            ;
    /* Collect fractional part */
    if (c == '.')
        while (isdigit(*s++ = c = *expr++))
            ;
    *s = '\0';
    if (c != EOF)
        expr--;

    return NUMBER_FOUND;
}
