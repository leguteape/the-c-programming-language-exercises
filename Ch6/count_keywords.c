/*
 * Program to count the C keywords in a file.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct key {
    char *word;
    int count;
} keytab[] = {{"auto", 0},     {"break", 0},    {"case", 0},     {"char", 0},
              {"const", 0},    {"continue", 0}, {"default", 0},  {"do", 0},
              {"double", 0},   {"else", 0},     {"enum", 0},     {"extern", 0},
              {"float", 0},    {"for", 0},      {"goto", 0},     {"if", 0},
              {"int", 0},      {"long", 0},     {"register", 0}, {"return", 0},
              {"short", 0},    {"signed", 0},   {"sizeof", 0},   {"static", 0},
              {"struct", 0},   {"switch", 0},   {"typedef", 0},  {"union", 0},
              {"unsigned", 0}, {"void", 0},     {"volatile", 0}, {"while", 0}};

#define MAXWORD 100
#define NKEYS ((int)(sizeof keytab / sizeof keytab[0]))

int getword(char *word, int limit);
struct key *binsearch(char *word, struct key *keytable, int table_size);

int main(void) {
    struct key *p;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
    for (p = keytab; p < keytab + NKEYS; p++)
        printf("%4d %s\n", p->count, p->word);

    return 0;
}

/*
 * NAME: binsearch
 * PURPOSE: To find whether the given word exists in a keyword table.
 * PARAMETERS:
 *  - char *word: The lookup word
 *  - struct key *tab: A pointer to the keyword table
 *  - int n: Size of the keyword table
 * RETURNS: Index of the keyword in the table; or
 *          -1 if word cannot be found in the table.
 */
struct key *binsearch(char *word, struct key *tab, int n) {
    struct key *mid;
    struct key *low = &tab[0];
    struct key *high = &tab[n];

    while (low < high) {
        int cond;

        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) > 0)
            low = mid + 1;
        else if (cond < 0)
            high = mid;
        else
            return mid;
    }

    return NULL;
}

/*
 * NAME: getword
 * PURPOSE: To get the next "word" from stdin.
 * PARAMETERS:
 *  - char *word: Buffer to hold the next word
 *  - int lim: The size of the buffer
 * RETURNS: The first character of the buffer; or
 *          the character itself if not alphabetic.
 */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getc(stdin)))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getc(stdin))) {
            ungetc(*w, stdin);
            break;
        }
    *w = '\0';
    return word[0];
}
