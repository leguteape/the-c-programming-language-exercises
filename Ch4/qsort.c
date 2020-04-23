#include <stdio.h>

#define VEC_LEN (int)(sizeof(vector) / sizeof(vector[0]))

/*
 * NAME: quicksort
 * PURPOSE: To sort an array of integers in ascending order.
 * PARAMETERS:
 *  - int vector[]: The array to sort
 *  - int left: The index of the leftmost element
 *  - int right: The index of the rightmost element
 * RETURNS: Nothing
 */
void quicksort(int vector[], int left, int right);

int main(void) {
    int i;
    int vector[] = {2, 1, 6, 4, 5, 3, 8, 7, 23, 0, 9};

    quicksort(vector, 0, VEC_LEN - 1);
    for (i = 0; i < VEC_LEN; i++)
        printf("%s%d", (i == 0) ? "" : ", ", vector[i]);
    printf("\n");

    return 0;
}

void quicksort(int v[], int left, int right) {
    int i, partition;
    void swap(int vector[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    partition = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++partition, i);
    swap(v, left, partition);

    quicksort(v, left, partition - 1);
    quicksort(v, partition + 1, right);
}

void swap(int v[], int i, int j) {
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
