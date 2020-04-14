/*
 * Program to implement binary search
 */

#include <assert.h>
#include <limits.h>
#include <math.h>

#define LENGTH 2000000

/*
 * NAME: binary_search
 * PURPOSE: Performs binary search upon a sorted array of numbers.
 * PARAMETERS:
 *  - int number: The item to find in the array
 *  - int array[]: The array of items to search
 *  - int length: The length of the array
 * RETURNS: the index of the number if found, -1 otherwise.
 */
int binary_search(int number, int array[], int length);

/*
 * NAME: initialize
 * PURPOSE: initialize a large array.
 * PARAMETERS:
 *  - int array[]: The array to initialize
 *  - int length: The length of the array
 * RETURNS: Nothing.
 */
void initialize(int array[], int length);

int main(void) {
    int arr[LENGTH];

    initialize(arr, LENGTH);
    assert(binary_search(1, arr, LENGTH) == 0);
    assert(binary_search(5, arr, LENGTH) == 4);
    assert(binary_search(556, arr, LENGTH) == 555);
    assert(binary_search(8, arr, LENGTH) == 7);
    assert(binary_search(arr[LENGTH - 1] + 1, arr, LENGTH) == -1);

    return 0;
}

int binary_search(int x, int v[], int n) {
    int low = 0, high = n - 1, mid = floor((low + high) / 2);

    while (low <= high) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = floor((low + high) / 2);
    }

    if (x == v[mid]) return mid;
    return -1;
}

void initialize(int arr[], int n) {
    for (int i = 0; i < n; ++i) arr[i] = i + 1;
}
