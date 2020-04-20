/* buffer.h */

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
 *  - int pushback_char: The character to push back
 * RETURNS: Nothing.
 */
void ungetch(int pushback_char);

/*
 * NAME: ungets
 * PURPOSE: To push an entire string back to input.
 * PARAMETERS:
 *  - char pushback_str[]: The string to push back
 * RETURNS: Nothing.
 */
void ungets(char pushback_str[]);
