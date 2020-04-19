/*
 * A simple postfix (reverse polish) calculator.
 */

/* main */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_OP_LEN 100
#define STORAGE_MAXLEN 25
#define NUMBER_FOUND '0'
#define VAR_ASSIGN_FOUND '1'
#define VAR_EXPAND_FOUND '2'
#define ANS_EXPAND_FOUND '3'
#define INVALID_VAR_USAGE '4'
#define NO_FUNC_FOUND '5'
#define SIN_FOUND '6'
#define COS_FOUND '7'
#define EXP_FOUND '8'

typedef enum { FALSE, TRUE } boolean;

/* Special storage for the last printed answer */
double ans;
/* The array to store values of variables */
double storage[STORAGE_MAXLEN];

/*
 * NAME: get_token
 * PURPOSE: To fetch an operator char directly or an operand in the buffer.
 * PARAMETERS:
 *  - char buffer[]: The buffer used to hold an operand
 * RETURNS: Either the operator itself, or a signal to indicate an operand.
 */
int get_token(char buffer[]);

/*
 * NAME: op_push
 * PURPOSE: To push a new element onto the top of the stack.
 * PARAMETERS:
 *  - double number: The number to push
 * RETURNS: Nothing.
 */
void op_push(double number);

/*
 * NAME: op_pop
 * PURPOSE: To pop out and return the topmost element from the stack.
 * PARAMETERS:
 *  - void
 * RETURNS: The topmost element of the stack.
 */
double op_pop(void);

/*
 * NAME: op_stacktop
 * PURPOSE: To return the topmost element from the stack without popping it.
 * PARAMETERS:
 *  - void
 * RETURNS: The topmost element of the stack.
 */
double op_stacktop(void);

/*
 * NAME: op_stackdup
 * PURPOSE: To push the top element onto the top of the stack again.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void op_stackdup(void);

/*
 * NAME: op_stackswap
 * PURPOSE: To swap the top two elements of a stack.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void op_stackswap(void);

/*
 * NAME: op_clear
 * PURPOSE: To clear the stack.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void op_stackclear(void);
/*
 * NAME: var_push
 * PURPOSE: To push a new element onto the top of the stack.
 * PARAMETERS:
 *  - char number: The number to push
 * RETURNS: Nothing.
 */
void var_push(char variable);

/*
 * NAME: var_pop
 * PURPOSE: To pop out and return the topmost element from the stack.
 * PARAMETERS:
 *  - void
 * RETURNS: The topmost element of the stack.
 */
char var_pop(void);

/*
 * NAME: var_stacktop
 * PURPOSE: To return the topmost element from the stack without popping it.
 * PARAMETERS:
 *  - void
 * RETURNS: The topmost element of the stack.
 */
char var_stacktop(void);

/*
 * NAME: var_instack
 * PURPOSE: To check if an item is in the vars stack.
 * PARAMETERS:
 *  - char to_find: The character to look for
 * RETURNS: TRUE or FALSE depending on presence of char in stack.
 */
boolean var_instack(char to_find);

/*
 * NAME: var_clear
 * PURPOSE: To clear the stack.
 * PARAMETERS:
 *  - void
 * RETURNS: Nothing.
 */
void var_stackclear(void);

int main(void) {
    int token;
    boolean error = FALSE;
    char strbuf[MAX_OP_LEN];

    while ((token = get_token(strbuf)) != EOF) {
        double op2;

        if (error) {
            if (token == '\n')
                error = FALSE;
            continue;
        }

        switch (token) {
        case NUMBER_FOUND:
            op_push(atof(strbuf));
            break;
        case ANS_EXPAND_FOUND:
            op_push(ans);
            break;
        case VAR_EXPAND_FOUND:
            /* During expansion, 'strbuf' holds a single letter variable */
            if (var_instack(strbuf[0]))
                op_push(storage[strbuf[0] - 'a']);
            else {
                printf("calculator: error: "
                       "Use of undefined variable '%s'\n",
                       strbuf);
                error = TRUE;
            }
            break;
        case SIN_FOUND:
            op_push(sin(op_pop()));
            break;
        case COS_FOUND:
            op_push(cos(op_pop()));
            break;
        case EXP_FOUND:
            op_push(exp(op_pop()));
            break;
        case '^':
            op2 = op_pop();
            op_push(pow(op_pop(), op2));
            break;
        case '*':
            op_push(op_pop() * op_pop());
            break;
        case '/':
            op2 = op_pop();
            if (op2 != 0.0)
                op_push(op_pop() / op2);
            else {
                printf("calculator: Zero divisor\n");
                error = TRUE;
            }
            break;
        case '%':
            op2 = op_pop();
            if (op2 != 0.0)
                op_push((int)op_pop() % (int)op2);
            else {
                printf("calculator: Zero divisor\n");
                error = TRUE;
            }
            break;
        case '+':
            op_push(op_pop() + op_pop());
            break;
        case '-':
            op2 = op_pop();
            op_push(op_pop() - op2);
            break;
        case VAR_ASSIGN_FOUND:
            /* For single letter variables only */
            var_push(strbuf[0]);
            break;
        case '=':
            op_push(storage[var_stacktop() - 'a'] = op_pop());
            break;
        case '\n':
            printf("\t%.8g\n", (ans = op_pop()));
            break;
        default:
            printf("calculator: Unknown command '%s'\n", strbuf);
            error = TRUE;
            break;
        }
    }

    return 0;
}

/* stack */

#define OPERANDS_MAX_DEPTH 100
#define VARS_MAX_DEPTH 100

int osp = -1; /* -1 indicates empty stack */
int vsp = -1;
double operands[OPERANDS_MAX_DEPTH];
char vars[VARS_MAX_DEPTH];

void op_push(double f) {
    if (osp >= OPERANDS_MAX_DEPTH - 1)
        printf("op_push: error: Stack overflow\n");
    else
        operands[++osp] = f;
}

double op_pop(void) {
    if (osp < 0) {
        printf("op_pop: error: Stack underflow\n");
        return 0.0;
    } else
        return operands[osp--];
}

double op_stacktop(void) {
    if (osp < 0) {
        printf("op_stacktop: error: Stack is empty\n");
        return 0.0;
    } else
        return operands[osp];
}

void op_stackdup(void) {
    if (osp < 0)
        printf("op_stackdup: error: Stack is empty\n");
    else if (osp >= OPERANDS_MAX_DEPTH - 1)
        printf("op_stackdup: error: Stack overflow\n");
    else {
        operands[osp + 1] = operands[osp];
        ++osp;
    }
}

void op_stackswap(void) {
    double top;

    if (osp <= 0)
        printf("op_stackswap: error: Stack doesn't contain enough items\n");
    else {
        top = operands[osp];
        operands[osp] = operands[osp - 1];
        operands[osp - 1] = top;
    }
}

void op_stackclear(void) { osp = -1; }

void var_push(char v) {
    if (vsp >= VARS_MAX_DEPTH - 1)
        printf("var_push: error: Stack overflow\n");
    else
        vars[++vsp] = v;
}

char var_pop(void) {
    if (vsp < 0) {
        printf("var_pop: error: Stack underflow\n");
        return 0.0;
    } else
        return vars[vsp--];
}

char var_stacktop(void) {
    if (vsp < 0) {
        printf("var_stacktop: error: Stack is empty\n");
        return '\0';
    } else
        return vars[vsp];
}

boolean var_instack(char c) {
    int i;

    if (vsp < 0) {
        printf("var_instack: error: Stack is empty\n");
        return FALSE;
    }
    for (i = vsp; i >= 0; i--)
        if (c == vars[i])
            return TRUE;
    return FALSE;
}

void var_stackclear(void) { vsp = -1; }

/* get_token */

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
 *  - char buffer[]: The string buffer
 * RETURNS: Code based on the type of function.
 */
int get_function(char buffer[]);

/*
 * NAME: get_operand
 * PURPOSE: To get the operand in the string buffer.
 * PARAMETERS:
 *  - char buffer[]: The string buffer
 *  - int curr_index: The current index into the buffer
 * RETURNS: Nothing.
 */
void get_operand(char buffer[], int curr_index);

/*
 * NAME: get_var_name
 * PURPOSE: To get the value of the variable in the buffer.
 * PARAMETERS:
 *  - char buffer[]: The string buffer
 * RETURNS: Status indicating whether var name is valid or not.
 */
int get_var_name(char buffer[]);

#include <ctype.h>
#include <string.h>

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
            int vstatus;

            /* '$' is used for variable expansion (like in the shell) */
            if (isalpha(s[++i] = c = getch())) {
                ungetch(c);
                if ((vstatus = get_var_name(s)) != INVALID_VAR_USAGE)
                    return vstatus;
            }
        } else if (isalpha(c)) {
            int ftype;

            ungetch(c);
            if ((ftype = get_function(s)) != NO_FUNC_FOUND)
                return ftype;
            /* Handle errors related to invalid variable use */
            while ((c = getch()) == ' ' || c == '\t')
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
        return INVALID_VAR_USAGE;
    }
}

/* buffer */

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
