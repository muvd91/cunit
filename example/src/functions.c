#include "myLib.h"
#include <string.h>
#include<stdlib.h>
#include<stdio.h>

int
factorial(int n) {
    if (n == 1)
        return (1);
    return n * factorial(n - 1);
}

int power(int base, int exp) {
    if (exp == 1 || exp == 0)
        return base;
    return base * power(base, exp - 1);
}

char *myTrim(const char *str) {
    int len = strlen(str);
    char *trimmed = (char *) malloc(len);
    char *initTrim = trimmed;

    int to = len - 1;
    while(*(str + to) == 32) to--;
    int copy = 0;
    while (to-- >= 0) {
        if (*str != 32)
            copy = 1;
        if (copy)
            *trimmed++ = *str;
        str++;
    }
    trimmed = initTrim;
    return trimmed;
}
