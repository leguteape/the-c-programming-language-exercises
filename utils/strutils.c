#include <stdio.h>

int length(const char *s) {
    int len = 0;

    while (*s++ != '\0')
        ++len;

    return len;
}

void reverse(char *s) {
    char tmp;
    int start, end;

    for (start = 0, end = length(s) - 1; end > start; --end, ++start) {
        tmp = s[end];
        s[end] = s[start];
        s[start] = tmp;
    }
}

char *trim(char *s) {
    int len = length(s);
    int curr;

    // If string is empty, i.e. contains only a '\n'
    if (len <= 1)
        return "";

    curr = len - 1;
    // If the current line has '\n', '\t' or ' ' at the end, keep reducing the
    // counter
    while (curr >= 0 && (s[curr] == '\n' || s[curr] == '\t' || s[curr] == ' '))
        --curr;
    // This test ensures that any lines containing only whitespaces
    // will be removed too
    if (curr < 0)
        return "";
    // Here len - 1 is used to account for the '\n' at the end
    else if (curr < len - 1) {
        s[curr + 1] = '\n';
        s[curr + 2] = '\0';
    }

    return s;
}

size_t get_line(char *s, int lim) {
    int c;
    char *p = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = '\0';

    return p - s;
}
