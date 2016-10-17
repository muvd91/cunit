#include "mathfn.h"

int
factorial(int n) {
    if (n == 1)
        return (1);
    return n * factorial(n - 1);
}

int power(int base, int exp) {
    if (exp == 1)
        return base;
    return base * power(base, exp - 1);
}
