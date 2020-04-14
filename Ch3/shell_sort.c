/*
 * Program to sort an array of numbers in ascending order
 * using Shell sort.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define LENGTH (int)(sizeof(numbers) / sizeof(numbers[0]))

/*
 * NAME: shellsort
 * PURPOSE: To sort an array of numbers in ascending order
 *          using shell sort.
 * PARAMETERS:
 *  - int array[]: The array to sort
 *  - int length: The length of the array
 * RETURNS: Nothing
 */
void shellsort(int array[], int length);

/*
 * NAME: is_equal
 * PURPOSE: To check if 2 arrays of the same length are "equal".
 * PARAMETERS:
 *  - int array1[]: The first array
 *  - int array2[]: The second array
 *  - int length: The length of both arrays
 * RETURNS: Nothing.
 */
bool is_equal(int array1[], int array2[], int length);

int main(void) {
    int numbers[] = {22, 20, 19, 17, 15, 12, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 15, 17, 19, 20, 22};

    shellsort(numbers, LENGTH);
    assert(is_equal(numbers, sorted, LENGTH));

    return 0;
}

void shellsort(int v[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++)
            for (int j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                int temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}

bool is_equal(int a1[], int a2[], int n) {
    for (int i = 0; i < n; i++)
        if (a1[i] != a2[i]) return false;

    return true;
}
