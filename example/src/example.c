#include "myLib.h"
#include "cunit.h"

void test_factorial(void);
void test_power(void);
void test_myTrim(void);

int
main() {
    test("Factorial testing", &test_factorial);
    test("Power testing", &test_power);
    test("String testing", &test_myTrim);
    print_results();
    return 0;
}

void
test_power() {
    assert_equal_numbers("2 ^ 5 should equal 32", 32, power(2,5));
    assert_equal_numbers("2 ^ 4 should equal 16", 16, power(2,4));
    assert_equal_numbers("2 ^ 3 should equal 8", 8, power(2,3));
    assert_equal_numbers("2 ^ 2 should equal 4", 4, power(2,2));
    assert_equal_numbers("2 ^ 1 should equal 2", 2, power(2,1));
    assert_equal_numbers("2 ^ 0 should equal 1", 1, power(2,0));
}

void
test_factorial() {
    assert_equal_numbers("5! should equal 120", 120, factorial(5));
    assert_equal_numbers("4! should equal 24", 24, factorial(4));
    assert_equal_numbers("3! should equal 6", 6, factorial(3));
    assert_equal_numbers("2! should equal 2", 2, factorial(2));
    assert_equal_numbers("1! should equal 1", 1, factorial(1));
    assert_true("2^2 is bigger than 0", power(2,2) > 0);
}

void
test_myTrim() {
    assert_equal_strings("Should trim leading spaces", "trimMe", myTrim("trimMe   "));
    assert_equal_strings("Should trim trailing spaces", "trimMe", myTrim("   trimMe"));
    assert_equal_strings("Should trim leading and trailing spaces", "trimMe", myTrim("   trimMe   "));
    assert_equal_strings("Should not trim in-between spaces", "trim  Me", myTrim("   trim  Me   "));
    assert_equal_strings("Empty string should return empty string", "", myTrim(""));
    assert_equal_strings("Two space should return empty string", "", myTrim("  "));
    assert_equal_strings("One space should return empty string", "", myTrim(" "));
}
