#include <stdio.h>

int main(void) {
    float celsius, fahr;
    int lower = 0, upper = 300, step = 20;

    celsius = lower;
    printf("Celsius\tFahrenheit\n");
    while (celsius <= upper) {
        fahr = ((9.0 / 5.0) * celsius) + 32.0;
        printf("%7.0f\t%10.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}
