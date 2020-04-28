#include <assert.h>
#include <string.h>

#define MAXLEN 1000

/*
 * NAME:strend
 * PURPOSE: Check if a substring appears at the end of the given string.
 * PARAMETERS:
 *  - char *target: The target string to search in
 *  - char *source: The string to search for
 * RETURNS: 1 if substring found, 0 otherwise.
 */
int strend(const char *target, const char *search);

int main(void) {
    char *t1 = "apple";
    char *t2 = "apple app";
    char *t3 = "mobile app";
    char *search = "app";

    assert(strend(t1, search) == 0);
    assert(strend(t2, search) == 1);
    assert(strend(t3, search) == 1);

    return 0;
}

int strend(const char *t, const char *s) {
    const char *p = s;

    while (*t) {
        while (*t && *p && *t++ == *p)
            p++;
        if (!*t && !*p)
            return 1;
        else
            p = s;
    }

    return 0;
}
