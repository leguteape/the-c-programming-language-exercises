#ifndef STRUTILS_H_
#define STRUTILS_H_

/*
 * NAME: length
 * PURPOSE: To find the length of a string (character array)
 * PARAMETERS:
 *      - const char *line: The string to find the length of
 * RETURNS: Length of the given string
 */
int length(const char *line);

/*
 * NAME: reverse
 * PURPOSE: To reverse the given string
 * PARAMETERS:
 *      - char *line: The string to reverse
 * RETURNS: Nothing
 * SIDE EFFECTS: Changes the original parameter to get reverse
 */
void reverse(char *line);

/*
 * NAME trim
 * PURPOSE: To trim out trailing blanks and tabs and also remove blank lines.
 * PARAMETERS:
 *      - char *line: The string to trim
 * RETURNS: The trimmed string
 * SIDE EFFECTS: Changes the original parameter
 */
char *trim(char *line);

/*
 * NAME: get_line
 * PURPOSE: To get a line of input from the keyboard (stdin)
 * PARAMETERS:
 *      - char line[]: The buffer to store the input line
 *      - int maxlen: The maximum length of the buffer
 * RETURNS: Length of the input line (or zero for EOF)
 */
int get_line(char line[], int maxlen);

#endif
