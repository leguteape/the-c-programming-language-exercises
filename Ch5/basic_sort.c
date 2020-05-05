/*
 * Program to perform alphabetical sorting of strings.
 */

#include <stdio.h>
#include <time.h>

#define MAXLINES 5000
#define BUFSIZE 10000

/*
 * NAME: quicksort
 * PURPOSE: To sort an array of lines using quicksort algorithm.
 * PARAMETERS:
 *  = char *lines[]: An array of pointers to lines
 *  - int left: The start index of the sub-array to sort
 *  - int right: The end index of the sub-array to sort, inclusive
 * RETURNS: Nothing.
 */
void quicksort(char *lines[], int left, int right);

/*
 * NAME: writelines
 * PURPOSE: To print lines to stdout.
 * PARAMETERS:
 *  - char *lineptrs[]: An array of pointers to lines
 *  - int nlines: The number of lines in the array
 * RETURNS: Nothing.
 */
void writelines(char *lineptrs[], int nlines);

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
int readlines(char *lineptrs[], int maxlines, char *buffer, int bufsize);

int main(void) {
    int nlines;
    char buffer[BUFSIZE];
    char *lineptrs[MAXLINES];

    clock_t begin = clock();
    nlines = readlines(lineptrs, MAXLINES, buffer, BUFSIZE);
    clock_t end = clock();
    printf("Took %g sec to read input.\n",
           (double)(end - begin) / CLOCKS_PER_SEC);
    if ((nlines) >= 0) {
        quicksort(lineptrs, 0, nlines - 1);
        writelines(lineptrs, nlines);
        return 0;
    } else {
        printf("error: Input too big to sort\n");
        return -1;
    }
}

#include <string.h>

void quicksort(char *v[], int left, int right) {
    int pivot, i;
    void swap(char *array[], int left, int right);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    pivot = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++pivot, i);
    swap(v, pivot, left);

    quicksort(v, left, pivot - 1);
    quicksort(v, pivot + 1, right);
}

void writelines(char *lineptrs[], int nlines) {
    while (--nlines >= 0)
        printf("%s\n", *lineptrs++);
}

#include "../include/allocator.h"
#include "../include/strutils.h"

#define MAXLEN 1000

int readlines(char *lineptrs[], int maxlines, char *buf, int bufsize) {
    int nlines, len;
    char *p;
    char line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* Remove the trailing newline */
            strcpy(p, line);
            lineptrs[nlines++] = p;
            /*
             * buf += len;
             * bsize += len;
             */
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
void swap(char *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
