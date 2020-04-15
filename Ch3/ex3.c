/*
 * Program to expand shorthand notation like a-z into
 * their full forms like abcd...xyz.
 */

#include <assert.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000

/*
 * NAME: expand
 * PURPOSE: To expand shorthand notation (like a-z) in
 *          source string to full notation (like abc...xyz)
 *          in the target string.
 * PARAMETERS:
 *  - char source[]: The source string
 *  - char target[]: The destination string
 *  - int max_length: The maximum length of the buffer
 * RETURNS: Nothing.
 * NOTE: This function works only for ASCII-compatible
 *       character sets.
 */
void expand(char source[], char target[], int max_length);

int main(void) {
    char dest[MAXLEN];

    expand("a-z", dest, MAXLEN);
    assert(strcmp(dest, "abcdefghijklmnopqrstuvwxyz") == 0);
    expand("e-x", dest, MAXLEN);
    assert(strcmp(dest, "efghijklmnopqrstuvwx") == 0);
    expand("lA-F", dest, MAXLEN);
    assert(strcmp(dest, "lABCDEF") == 0);
    expand("b-h0-9I-V", dest, MAXLEN);
    assert(strcmp(dest, "bcdefgh0123456789IJKLMNOPQRSTUV") == 0);
    expand("0b-f8", dest, MAXLEN);
    assert(strcmp(dest, "0bcdef8") == 0);
    expand("pa-b-glr", dest, MAXLEN);
    assert(strcmp(dest, "pabcdefglr") == 0);
    expand("-a-hlQ-", dest, MAXLEN);
    assert(strcmp(dest, "-abcdefghlQ-") == 0);
    expand("-a-h-nq-", dest, MAXLEN);
    assert(strcmp(dest, "-abcdefghijklmnq-") == 0);

    return 0;
}

void expand(char s[], char t[], int lim) {
    int dest = 0;

    for (int i = 0; dest < lim - 1 && s[i] != '\0'; i++)
        if (i > 0 && s[i] == '-' && (isalpha(s[i - 1]) || isdigit(s[i - 1])) &&
            (isalpha(s[i + 1]) || isdigit(s[i + 1])))
            for (char c = s[i - 1] + 1; dest < lim - 1 && c < s[i + 1]; c++)
                t[dest++] = c;
        else
            t[dest++] = s[i];
    t[dest] = '\0';
}
