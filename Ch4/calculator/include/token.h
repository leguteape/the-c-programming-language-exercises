/* token.h */

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

/*
 * NAME: get_token
 * PURPOSE: To fetch an operator char directly or an operand in the buffer.
 * PARAMETERS:
 *  - char buffer[]: The buffer used to hold an operand
 * RETURNS: Either the operator itself, or a signal to indicate an operand.
 */
int get_token(char buffer[]);
