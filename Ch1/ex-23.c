/*
 * Program to remove all comments from a C program.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: remove_comments
 * PURPOSE: To remove all comments from a C program
 * PARAMETERS:
 *      - char *line: The line from which to remove comments
 * RETURNS: Nothing
 */
char *remove_comments(const char line[]);

int main(void) {
    char line[MAXLEN];
    char *decommented;

    while (get_line(line, MAXLEN) > 0) {
        decommented = remove_comments(line);
        printf("%s", trim(decommented));
        free(decommented);
    }

    return 0;
}

char *remove_comments(const char s[]) {
    int len = length(s), dest = 0;
    // Here, 'dest' will be used as an index
    // at which to copy non-comment characters.
    // Allocate a new string to copy the non-comment characters
    // in the line.
    char *decommented = malloc((len + 1) * sizeof(char));
    bool in_str_const = false, in_char_const = false;
    // The static variable 'in_prev_comment' will hold the state of
    // any open block-comments from previous lines
    static bool in_prev_comment = false;

    for (int i = 0; i < len; ++i) {
        if (!in_prev_comment && s[i] == '"') {
            // If a '"' character is found, it is possible that
            // comment needs to be ignored.
            //
            // So, we check if the '"' is not part of
            // a previous comment block.
            //
            // In case it isn't, we copy it to the destination
            // and check if it opens or closes a quoted string
            // and set the flag accordingly.
            decommented[dest++] = '"';
            if (!in_str_const)
                in_str_const = true;
            else
                in_str_const = false;
        } else if (!in_str_const && s[i] == '\'') {
            // The logic for comment openers in char constants
            // is similar to that for string constants,
            // except that we check for a '\'' instead of a '"'.
            //
            // See the comment for string constants above.
            decommented[dest++] = '\'';
            if (!in_char_const)
                in_char_const = true;
            else
                in_char_const = false;
        } else if (!in_prev_comment && !in_str_const && !in_char_const &&
                   i + 1 < len && s[i] == '/' && s[i + 1] == '/')
            // This test is for C99 style line-comments.
            //
            // The test checks whether any block-comments
            // are open from the lines before.
            //
            // If so, the line-comment (even if it exists) is ignored.
            // If not, it looks for two consecutive '/' characters.
            //
            // Upon finding the this combination, the remaining line is ignored.
            break;
        else if (in_prev_comment ||
                 (!in_str_const && !in_char_const && i + 1 < len &&
                  s[i] == '/' && s[i + 1] == '*')) {
            // This test is for traditional C comments.
            //
            // Block comments previously open are checked
            // using the 'in_prev_comment' variable.
            //
            // If a block comment is open from before, we check to
            // the end of the line to find a matching '*/' combo.
            //
            // If such a combo is found, the previous comment is closed.
            // If not, the previous comment is left open for following lines.
            //
            // As expected, any character between the
            // opening /* and closing */ are ignored.
            in_prev_comment = true;
            for (int j = i; j < len; ++j)
                if (s[j - 1] == '*' && s[j] == '/') {
                    // Close previously open block-comments
                    in_prev_comment = false;
                    break;
                } else
                    // Skip the current character
                    ++i;
        } else
            // If aforementioned combinations are not found, then
            // the current character is copied into the destination.
            decommented[dest++] = s[i];
    }
    // Terminate the destination string
    decommented[dest] = '\0';

    return decommented;
}
