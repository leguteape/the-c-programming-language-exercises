/* stack.c */

#include "calc.h"
#include <stdio.h>

#define OPERANDS_MAX_DEPTH 100
#define VARS_MAX_DEPTH 100

static int osp = -1; /* -1 indicates empty stack */
static int vsp = -1;
static double operands[OPERANDS_MAX_DEPTH];
static char vars[VARS_MAX_DEPTH];

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
        return VAR_STACK_EMPTY;
    } else
        return vars[vsp--];
}

char var_stacktop(void) {
    if (vsp < 0) {
        printf("var_stacktop: error: Stack is empty\n");
        return VAR_STACK_EMPTY;
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
