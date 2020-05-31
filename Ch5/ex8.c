/*
 * Program to implement date transformation from day of year
 * to day of month and vice versa.
 */

#include <assert.h>
#include <stdio.h>

#define MONTHS 13

static int daytable[][MONTHS] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void) {
    int m, d;

    assert(day_of_year(1988, 3, 1) == 61);
    assert(day_of_year(1998, 3, 1) == 60);

    month_day(1988, 61, &m, &d);
    assert(m == 3 && d == 1);
    month_day(1998, 60, &m, &d);
    assert(m == 3 && d == 1);

    /* Errors */
    assert(day_of_year(1988, 13, 1) == -1);
    assert(day_of_year(1988, 0, 1) == -1);
    assert(day_of_year(1998, 3, 32) == -1);
    assert(day_of_year(1988, 2, 29) != -1);
    assert(day_of_year(1998, 2, 28) != -1);
    assert(day_of_year(1998, 3, 0) == -1);

    month_day(1988, 367, &m, &d);
    assert(m == -1 && d == -1);
    month_day(1998, 366, &m, &d);
    assert(m == -1 && d == -1);

    return 0;
}

int day_of_year(int year, int month, int day) {
    int i, isleap;

    if (year < 0 || month <= 0 || month > 12 || day <= 0)
        return -1;

    isleap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day > *(*(daytable + isleap) + month))
        return -1;

    for (i = 0; i < month; i++)
        day += *(*(daytable + isleap) + i);

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int month, isleap;

    if (year < 0 || yearday <= 0) {
        *pmonth = *pday = -1;
        return;
    }

    isleap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    switch (isleap) {
    case 0:
        if (yearday > 365) {
            *pmonth = *pday = -1;
            return;
        }
        break;
    case 1:
        if (yearday > 366) {
            *pmonth = *pday = -1;
            return;
        }
        break;
    }

    for (month = 0; yearday > *(*(daytable + isleap) + month); month++)
        yearday -= *(*(daytable + isleap) + month);
    *pmonth = month;
    *pday = yearday;
}
