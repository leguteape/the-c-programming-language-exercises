/*
 * A simple postfix (reverse polish) calculator.
 */

/* main */

#include "calc.h"
#include "stack.h"
#include "token.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Special storage for the last printed answer */
double ans;
/* The array to store values of variables */
double storage[STORAGE_MAXLEN];

int main(void) {
    boolean error = FALSE;
    int token, var;
    char strbuf[MAX_OP_LEN];

    while ((token = get_token(strbuf)) != EOF) {
        double op2;

        /* Skip the rest of an erroneous line */
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
            if ((var = var_stacktop()) == VAR_STACK_EMPTY) {
                error = TRUE;
                printf("calculator: error: Invalid assignment expression\n");
            } else
                op_push(storage[var - 'a'] = op_pop());
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
