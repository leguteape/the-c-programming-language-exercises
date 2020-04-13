/*
 * Program to return the first location in a string where any
 * character of another string occurs, or -1 if none exist.
 */

#include <assert.h>

/*
 * NAME: any
 * PURPOSE: Program to return the first location in a string where any
 *          character of another string occurs, or -1 if none exist.
 * PARAMETERS:
 *      - char target_string[]: The string in which to find the characters
 *      - char chars_to_find[]: The string containing the characters to find
 * RETURNS: Index to the array target_string where first char is found or,
 *          -1 otherwise.
 */
int any(char target_string[], char chars_to_find[]);

int main(void) {
    char target[] = "Programming Language";
    char chars1[] = "Lmg", chars2[] = "nre";

    assert(any(target, chars1) == 3);
    assert(any(target, chars2) == 1);
    assert(any(target, "zxc") == -1);

    return 0;
}

int any(char s1[], char s2[]) {
    int index = -1;

    for (int i = 0; s2[i] != '\0'; ++i)
        for (int j = 0; s1[j] != '\0'; ++j)
            if (s1[j] == s2[i] && (index == -1 || index > j)) {
                index = j;
                break;
            }

    return index;
}
