#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void) {
    printf("Fahrenheit\tCelsius\n");
    for (int fahr = UPPER; fahr >= LOWER; fahr -= STEP)
        printf("%10d\t%7.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));

    return 0;
}
