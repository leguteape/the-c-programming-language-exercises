/*
 * A simple postfix (reverse polish) calculator.
 */

/* main */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_OP_LEN 100
#define NUMBER_FOUND '0'
#define VARIABLE_FOUND '1'
#define NO_FUNC_FOUND '2'
#define SIN_FOUND '3'
#define COS_FOUND '4'

typedef enum { FALSE, TRUE } boolean;

/*
 * NAME: getop
 * PURPOSE: To fetch an operator char directly or an operand in the buffer.
 * PARAMETERS:
 *  - char buffer[]: The buffer used to hold an operand
 * RETURNS: Either the operator itself, or a signal to indicate an operand.
 */
int getop(char buffer[]);

/*
 * NAME: push
 * PURPOSE: To push a new element onto the top of the stack.
 * PARAMETERS:
 *  - double number: The number to push
 * RETURNS: Nothing.
 */
void push(double number);

/*
 * NAME: pop
 * PURPOSE: To pop out and return the topmost element from the stack.
 * PARAMETERS:
 *  - void
 * RETURNS: The topmost element of the stack.
 */
double pop(void);

/*
 * NAME: stacktop
 * PURPOSE: To return the topmost element from the stack without popping it.
 * PARAMETERS:
 *  - void
 * RETURNS: The topmost element of the stack.
 */
double stacktop(void);

/*
 * NAME: stackdup
 * PURPOSE: To push the top element onto the top of the stack again.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void stackdup(void);

/*
 * NAME: stackswap
 * PURPOSE: To swap the top two elements of a stack.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void stackswap(void);

/*
 * NAME: clear
 * PURPOSE: To clear the stack.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void stackclear(void);

int main(void) {
    int optype;
    char str[MAX_OP_LEN];

    while ((optype = getop(str)) != EOF) {
        double op2;

        switch (optype) {
        case NUMBER_FOUND:
            push(atof(str));
            break;
        case VARIABLE_FOUND:
            printf("A Variable\n");
            break;
        case SIN_FOUND:
            push(sin(pop()));
            break;
        case COS_FOUND:
            push(cos(pop()));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("calculator: Zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("calculator: Zero divisor\n");
            break;
        case '^':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case 'e':
            push(exp(pop()));
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("calculator: Unknown command '%s'\n", str);
            break;
        }
    }

    return 0;
}

/* stack */

#define VAL_MAX_DEPTH 100

int sp = -1; /* -1 indicates empty stack */
double val[VAL_MAX_DEPTH];

void push(double f) {
    if (sp >= VAL_MAX_DEPTH - 1)
        printf("push: error: Stack overflow\n");
    else
        val[++sp] = f;
}

double pop(void) {
    if (sp < 0) {
        printf("pop: error: Stack underflow\n");
        return 0.0;
    } else
        return val[sp--];
}

double stacktop(void) {
    if (sp < 0) {
        printf("stacktop: error: Stack is empty\n");
        return 0.0;
    } else
        return val[sp];
}

void stackdup(void) {
    if (sp < 0)
        printf("stackdup: error: Stack is empty\n");
    else if (sp >= VAL_MAX_DEPTH - 1)
        printf("stackdup: error: Stack overflow\n");
    else {
        val[sp + 1] = val[sp];
        ++sp;
    }
}

void stackswap(void) {
    double top;

    if (sp <= 0)
        printf("stackswap: error: Stack doesn't contain enough items\n");
    else {
        top = val[sp];
        val[sp] = val[sp - 1];
        val[sp - 1] = top;
    }
}

void stackclear(void) { sp = -1; }

/* getop */

#include <ctype.h>

#define FUNC_BUF_SIZE 10

/*
 * NAME: getch
 * PURPOSE: To get a new character either from the push-back buffer
 *          or from the input stream.
 * PARAMETERS:
 *  - void
 * RETURNS: A new character
 */
int getch(void);

/*
 * NAME: ungetch
 * PURPOSE: To push a character back to the push-back buffer.
 * PARAMETERS:
 *  - void pushback_char: The character to push back
 * RETURNS: Nothing.
 */
void ungetch(int pushback_char);

/*
 * NAME: get_function
 * PURPOSE: To get the math function used in input.
 * PARAMETERS:
 *  - void
 * RETURNS: Code based on the type of function.
 */
int get_function(char buffer[]);

int getop(char s[]) {
    int c, i;

    /* Skip whitespace */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0'; /* Defence for the early return on finding operator */
    i = 0;
    /* Check for operator */
    if (!isdigit(c) && c != '.') {
        if (isalpha(c)) {
            int ftype;

            ungetch(c);
            if ((ftype = get_function(s)) != NO_FUNC_FOUND)
                return ftype;
            return VARIABLE_FOUND;
        } else if (c != '-') {
            /* Handle negative numbers */
            return c;
        } else if (c == '-' && !isdigit(s[++i] = c = getch())) {
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
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    /* Pur back the extra character read to determine end of an operand */
    if (c != EOF)
        ungetch(c);

    return NUMBER_FOUND;
}

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
    return NO_FUNC_FOUND;
}

#define BUFSIZE 100

char buffer[BUFSIZE];
int bufp = 0; /* Points at index of buffer where new char is inserted */

int getch(void) { return (bufp > 0) ? buffer[--bufp] : getchar(); }

void ungetch(int ch) {
    if (bufp >= BUFSIZE)
        printf("ungetch: error: Buffer overflow\n");
    else
        buffer[bufp++] = ch;
}
