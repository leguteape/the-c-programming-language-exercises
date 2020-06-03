/*
 * Program to perform alphabetical sorting of strings.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define BUFSIZE 10000

typedef enum { FALSE, TRUE } Boolean;

void quicksort(void *lineptr[], int left, int right,
               int (*comp)(void *, void *));

void writelines(char *lineptrs[], int nlines);
int readlines(char *lineptrs[], int maxlines, char *buffer, int bufsize);

int numcmp(const char *, const char *);
int fold_strcmp(const char *, const char *);
int directory_strcmp(const char *, const char *);
int directory_fold_strcmp(const char *, const char *);
int reverse_numcmp(const char *, const char *);
int reverse_strcmp(const char *, const char *);
int reverse_fold_strcmp(const char *, const char *);

int main(int argc, char *argv[]) {
    int nlines;
    char buffer[BUFSIZE];
    char *lineptrs[MAXLINES];
    void *compare_func;
    Boolean number = FALSE, reverse = FALSE;
    Boolean directory_order = FALSE, fold = FALSE;

    while (--argc > 0 && (*++argv)[0]) {
        int c;

        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                number = TRUE;
                break;
            case 'r':
                reverse = TRUE;
                break;
            case 'f':
                fold = TRUE;
                break;
            case 'd':
                directory_order = TRUE;
                break;
            default:
                fprintf(stderr, "quicksort: invalid option '%c'\n", c);
                return 1;
            }
        }
    }

    if (argc != 0) {
        fprintf(stderr, "Usage: quicksort [OPTIONS]");
        return 2;
    }

    if (number)
        compare_func = reverse ? reverse_numcmp : numcmp;
    else if (fold)
        if (directory_order)
            compare_func = directory_fold_strcmp;
        else
            compare_func = reverse ? reverse_fold_strcmp : fold_strcmp;
    else if (directory_order)
        compare_func = directory_strcmp;
    else
        compare_func = reverse ? reverse_strcmp : strcmp;

    if ((nlines = readlines(lineptrs, MAXLINES, buffer, BUFSIZE)) >= 0) {
        quicksort((void **)lineptrs, 0, nlines - 1,
                  (int (*)(void *, void *))compare_func);
        writelines(lineptrs, nlines);
        return 0;
    } else {
        printf("error: Input too big to sort\n");
        return 3;
    }
}

/*
 * NAME: quicksort
 * PURPOSE: To sort an array of lines using quicksort algorithm.
 * PARAMETERS:
 *  = char *lineptr[]: An array of pointers to lines
 *  - int left: The start index of the sub-array to sort
 *  - int right: The end index of the sub-array to sort, inclusive
 * RETURNS: Nothing.
 */
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int pivot, i;
    void swap(void *array[], int left, int right);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    pivot = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++pivot, i);
    swap(v, pivot, left);

    quicksort(v, left, pivot - 1, comp);
    quicksort(v, pivot + 1, right, comp);
}

/*
 * NAME: writelines
 * PURPOSE: To print lines to stdout.
 * PARAMETERS:
 *  - char *lineptrs[]: An array of pointers to lines
 *  - int nlines: The number of lines in the array
 * RETURNS: Nothing.
 */
void writelines(char *lineptrs[], int nlines) {
    while (--nlines >= 0)
        printf("%s\n", *lineptrs++);
}

#include "../include/strutils.h"

#define MAXLEN 1000

/*
 * NAME: readlines
 * PURPOSE: To read all the input lines provided by the user.
 * PARAMETERS:
 *  - char *lineptrs[]: An array of pointers to lines
 *  - int maxlines: The maximum number of allowable lines
 *  - char *buffer: The buffer to place the strings in
 *  - int bufsize: Size of the buffer
 * RETURNS: The number of lines read on success, -1 on failure.
 */
int readlines(char *lineptrs[], int maxlines, char *buf, int bufsize) {
    int nlines, len, bsize;
    char line[MAXLEN];

    nlines = 0, bsize = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || bsize >= bufsize)
            return -1;
        else {
            line[len - 1] = '\0'; /* Remove the trailing newline */
            strcpy(buf, line);
            lineptrs[nlines++] = buf;
            buf += len;
            bsize += len;
        }
    return nlines;
}

/*
 * NAME: swap
 * PURPOSE: To swap two pointers to char.
 * PARAMETERS:
 *  - char *v[]: The array of pointers to char
 *  - int i: The first index
 *  - int j: The second index
 * RETURNS: Nothing.
 * SIDE EFFECTS: Mutates the given array.
 */
void swap(void *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#include <stdlib.h>

/*
 * NAME: numcmp
 * PURPOSE: To compare two stringified numbers.
 * PARAMETERS:
 *  - const char *s1: The first stringified number
 *  - const char *s2: The second stringified number
 * RETURNS: -1; if s1 < s2
 *           1; if s1 > s2
 *           0; otherwise.
 */
int numcmp(const char *s1, const char *s2) {
    int v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/*
 * NAME: reverse_numcmp
 * PURPOSE: To compare two stringified numbers.
 * PARAMETERS:
 *  - const char *s1: The first stringified number
 *  - const char *s2: The second stringified number
 * RETURNS:  1; if s1 < s2
 *          -1; if s1 > s2
 *           0; otherwise.
 */
int reverse_numcmp(const char *s1, const char *s2) {
    int v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 > v2)
        return -1;
    else if (v1 < v2)
        return 1;
    else
        return 0;
}

/*
 * NAME: reverse_strcmp
 * PURPOSE: To compare two strings.
 * PARAMETERS:
 *  - const char *s1: The first stringified number
 *  - const char *s2: The second stringified number
 * RETURNS:  1; if s1 < s2
 *          -1; if s1 > s2
 *           0; otherwise.
 */
int reverse_strcmp(const char *s1, const char *s2) { return strcmp(s2, s1); }

#include <ctype.h>

/*
 * NAME: fold_strcmp
 * PURPOSE: To compare two strings case-insensitively.
 * PARAMETERS:
 *  - const char *s1: The first string
 *  - const char *s2: The second string
 * RETURNS: -1; if s1 < s2
 *           1; if s1 > s2
 *           0; otherwise.
 */
int fold_strcmp(const char *s1, const char *s2) {
    char *p1, *p2, *p;
    int result;

    p = p1 = malloc(strlen(s1) + 1);
    while ((*p = toupper(*s1++)))
        p++;
    p = p2 = malloc(strlen(s2) + 1);
    while ((*p = toupper(*s2++)))
        p++;
    result = strcmp(p1, p2);

    free(p1);
    free(p2);
    return result;
}

/*
 * NAME: reverse_fold_strcmp
 * PURPOSE: To compare two strings case-insensitively.
 * PARAMETERS:
 *  - const char *s1: The first string
 *  - const char *s2: The second string
 * RETURNS:  1; if s1 < s2
 *          -1; if s1 > s2
 *           0; otherwise.
 */
int reverse_fold_strcmp(const char *s1, const char *s2) {
    return fold_strcmp(s2, s1);
}

/*
 * NAME: directory_fold_strcmp
 * PURPOSE: To compare two strings in directory-order.
 * PARAMETERS:
 *  - const char *s1: The first string
 *  - const char *s2: The second string
 * RETURNS: -1; if s1 < s2
 *           1; if s1 > s2
 *           0; otherwise.
 */
int directory_strcmp(const char *s1, const char *s2) {
    char *p1, *p2, *p;
    int result;

    p1 = malloc(strlen(s1) + 1);
    for (p = p1; *s1; s1++)
        if (isalnum(*s1) || *s1 == ' ' || *s1 == '\t')
            *p++ = *s1;
    *p = '\0';
    p2 = malloc(strlen(s2) + 1);
    for (p = p2; *s2; s2++)
        if (isalnum(*s2) || *s2 == ' ' || *s2 == '\t')
            *p++ = *s2;
    *p = '\0';
    result = strcmp(p1, p2);

    free(p1);
    free(p2);
    return result;
}

/*
 * NAME: directory_fold_strcmp
 * PURPOSE: To compare two strings case-insensitively, in directory-order.
 * PARAMETERS:
 *  - const char *s1: The first string
 *  - const char *s2: The second string
 * RETURNS: -1; if s1 < s2
 *           1; if s1 > s2
 *           0; otherwise.
 */
int directory_fold_strcmp(const char *s1, const char *s2) {
    char *p1, *p2, *p;
    int result;

    p1 = malloc(strlen(s1) + 1);
    for (p = p1; *s1; s1++)
        if (isalnum(*s1) || *s1 == ' ' || *s1 == '\t')
            *p++ = toupper(*s1);
    *p = '\0';
    p2 = malloc(strlen(s2) + 1);
    for (p = p2; *s2; s2++)
        if (isalnum(*s2) || *s2 == ' ' || *s2 == '\t')
            *p++ = toupper(*s2);
    *p = '\0';
    result = strcmp(p1, p2);

    free(p1);
    free(p2);
    return result;
}
