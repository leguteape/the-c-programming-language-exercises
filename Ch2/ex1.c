/*
 * program to determine the ranges of char, short, int, and long
 * variables (both signed and unsigned versions)
 * by printing values from the standard header
 * and by computation.
 */

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    printf("Using standard header:\n");
    printf("Signed types:\n");
    printf("SCHAR_MAX = %d\n", SCHAR_MAX);
    printf("SCHAR_MIN = %d\n", SCHAR_MIN);
    printf("INT_MAX = %d\n", INT_MAX);
    printf("INT_MIN = %d\n", INT_MIN);
    printf("LONG_MAX = %ld\n", LONG_MAX);
    printf("LONG_MIN = %ld\n", LONG_MIN);
    printf("LLONG_MAX = %lld\n", LLONG_MAX);
    printf("LLONG_MIN = %lld\n", LLONG_MIN);
    printf("Unsigned types:\n");
    printf("UCHAR_MAX = %u\n", UCHAR_MAX);
    printf("UINT_MAX = %u\n", UINT_MAX);
    printf("ULONG_MAX = %lu\n", ULONG_MAX);
    printf("ULLONG_MAX = %llu\n", ULLONG_MAX);
    printf("Floating types:\n");
    printf("FLOAT_MAX = %e\n", FLT_MAX);
    printf("FLOAT_MIN = %e\n", FLT_MIN);
    printf("DOUBLE_MAX = %e\n", DBL_MAX);
    printf("DOUBLE_MIN = %e\n", DBL_MIN);
    printf("LDOUBLE_MAX = %Le\n", LDBL_MAX);
    printf("LDOUBLE_MIN = %Le\n", LDBL_MIN);

    printf("\nUsing computation:\n");
    printf("Signed types:\n");
    printf("SCHAR_MAX = %.0f\n", pow(2, sizeof(signed char) * 8 - 1) - 1);
    printf("SCHAR_MIN = %.0f\n", -pow(2, sizeof(signed char) * 8 - 1));
    printf("INT_MAX = %.0f\n", pow(2, sizeof(int) * 8 - 1) - 1);
    printf("INT_MIN = %.0f\n", -pow(2, sizeof(int) * 8 - 1));
    printf("LONG_MAX = %.0f\n", pow(2, sizeof(long) * 8 - 1) - 1);
    printf("LONG_MIN = %.0f\n", -pow(2, sizeof(long) * 8 - 1));
    printf("LLONG_MAX = %.0f\n", pow(2, sizeof(long long) * 8 - 1) - 1);
    printf("LLONG_MIN = %.0f\n", -pow(2, sizeof(long long) * 8 - 1));
    printf("Unsigned types:\n");
    printf("UCHAR_MAX = %.0f\n", pow(2, sizeof(unsigned char) * 8) - 1);
    printf("UINT_MAX = %.0f\n", pow(2, sizeof(unsigned int) * 8) - 1);
    printf("ULONG_MAX = %.0f\n", pow(2, sizeof(unsigned long) * 8) - 1);
    printf("ULLONG_MAX = %.0f\n", pow(2, sizeof(unsigned long long) * 8) - 1);

    return 0;
}
