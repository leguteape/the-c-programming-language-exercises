#include <assert.h>
#include <string.h>

#define MAXLEN 1000

/*
 * NAME: strncopy
 * PURPOSE: To copy the first n characters of source to target string.
 * PARAMETERS:
 *  - char *target: The target string
 *  - char *source: The source string
 *  - int count: The number of characters to copy
 * RETURNS: Nothing.
 * SIDE EFFECTS: Changes the target string.
 */
void strncopy(char *target, const char *source, int n);

/*
 * NAME: strnconcat
 * PURPOSE: Concatenates n characters of the source string
 *          into the target string.
 * PARAMETERS:
 *  - char *target: The target string
 *  - char *source: The source string
 *  - int count: The number of characters to concatenate
 * RETURNS: Nothing.
 * SIDE EFFECTS: Changes the target string.
 */
void strnconcat(char *target, const char *source, int n);

/*
 * NAME:strncompare
 * PURPOSE: To find which of the given two strings
 *          is "greater" lexicographically.
 * PARAMETERS:
 *  - char *str1: The target string to search in
 *  - char *str2: The string to search for
 *  - int count: The number of first few character to compare
 * RETURNS: 0 if str1 == str2,
 *          negative value if str1 < str2 and
 *          positive value otherwise.
 */
int strncompare(const char *str1, const char *str2, int count);

int main(void) {
    char target[MAXLEN] = "Apple";
    char *source = " Computer";

    strnconcat(target, source, 4);
    assert(strcmp(target, "Apple Com") == 0);
    strnconcat(target, source, 11);
    assert(strcmp(target, "Apple Com Computer") == 0);

    strncopy(target, source, 4);
    assert(strcmp(target, " Com") == 0);
    strncopy(target, source, 11);
    assert(strcmp(target, " Computer") == 0);

    assert(strncompare("Apple", "App Store", 3) == 0);
    assert(strncompare("Apple", "App Store", 5) > 0);

    return 0;
}

void strncopy(char *t, const char *s, int n) {
    while (--n >= 0 && (*t++ = *s++))
        ;
    if (n < 0)
        *t = '\0';
}

void strnconcat(char *t, const char *s, int n) {
    while (*t)
        t++;
    while (--n >= 0 && (*t++ = *s++))
        ;
    if (n < 0)
        *t = '\0';
}

int strncompare(const char *s1, const char *s2, int n) {
    for (; --n >= 0 && *s1 == *s2; s1++, s2++)
        if (!*s1)
            return 0;

    if (n < 0)
        return 0;
    return *s1 - *s2;
}
