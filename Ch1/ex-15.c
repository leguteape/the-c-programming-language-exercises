#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

void print_table(int lower, int upper, int step);

int main(void) {
    print_table(LOWER, UPPER, STEP);

    return 0;
}

void print_table(int low, int high, int step) {
    printf("Fahrenheit\tCelsius\n");
    for (; low <= high; low += step)
        printf("%10d\t%7.1f\n", low, (5.0 / 9.0) * (low - 32.0));
}
