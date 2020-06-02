#include <stdio.h>

int main(void) {
    printf("%d\n", -5 % 3);
    printf("%d\n", 5 % -3);
    printf("%d\n", -5 % -3);

    char *str =
        "hello"
        " world!";
    printf("%s\n", str);
}
