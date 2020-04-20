/* stack.h */

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
