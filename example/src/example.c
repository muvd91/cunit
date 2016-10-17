#include "mathfn.h"
#include "cunit.h"

void test_factorial(void);
void test_power(void);

int
main() {
    test("Factorial testing", &test_factorial);
    test("Power testing", &test_power);
    print_results();
    return 0;
}

void
test_power() {
    assert_equals_number("2 ^ 5 should equal 32", 32, power(2,5));
    assert_equals_number("2 ^ 4 should equal 16", 16, power(2,4));
    assert_equals_number("2 ^ 3 should equal 8", 8, power(2,3));
    assert_equals_number("2 ^ 2 should equal 4", 4, power(2,2));
    assert_equals_number("2 ^ 1 should equal 2", 2, power(2,1));
}

void
test_factorial() {
    assert_equals_number("5! should equal 120", 120, factorial(5));
    assert_equals_number("4! should equal 24", 24, factorial(4));
    assert_equals_number("3! should equal 6", 6, factorial(3));
    assert_equals_number("2! should equal 2", 2, factorial(2));
    assert_equals_number("1! should equal 1", 1, factorial(1));
}

