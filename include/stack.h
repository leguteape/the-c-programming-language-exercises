#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <stdbool.h>

typedef struct node {
    char element;
    struct node *next;
} Node;

typedef struct {
    int size;
    Node top;
} Stack;

/*
 * NAME:create_stack
 * PURPOSE: To create a new stack
 * PARAMETERS:
 *      None
 * RETURNS: Pointer to the head of the new stack
 */
Stack *create_stack();

/*
 * NAME: empty
 * PURPOSE: Checks if the stack is empty
 * PARAMETERS:
 *      - Stack *stk: Pointer to the stack
 * RETURNS: true if stack is empty; false otherwise
 */
bool empty(Stack *stk);

/*
 * NAME: full
 * PURPOSE: Checks if the stack is full
 * PARAMETERS:
 *      - Stack *stk: Pointer to the stack
 * RETURNS: true if stack is full; false otherwise
 */
bool full(Stack *stk);

/*
 * NAME: push
 * PURPOSE: Pushes a new element onto the stack
 * PARAMETERS:
 *      - Stack *stk: Pointer to the stack
 *      - char element: The item to be puched
 * RETURNS: Nothing
 */
void push(Stack *stk, char element);

/*
 * NAME: pop
 * PURPOSE: Pops the element at the top of the stack
 * PARAMETERS:
 *      - Stack *stk: Pointer to the stack
 * RETURNS: The character at the top
 */
char pop(Stack *stk);

/*
 * NAME: stacktop
 * PURPOSE: Fetches the item at the top of the stack without popping it
 * PARAMETERS:
 *      - Stack *stk: Pointer to the stack
 * RETURNS: The character at the top
 */
char stacktop(Stack *stk);

#endif // INCLUDE_STACK_H_
