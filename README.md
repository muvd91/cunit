# cunit

**Step 1**: 
Include cunit.h and register your test.
```c
#include "cunit.h"
int
main() {
    test("Factorial testing", &test_factorial);
    test("Power testing", &test_power);
    test("String testing", &test_myTrim);
    print_results();
    return 0;
}
```
**Step 2**: 
Test your code through the use of asserts
```c
void
test_power() {
    assert_equal_numbers("2 ^ 3 should equal 8", 8, power(2,3));
    assert_equal_numbers("2 ^ 2 should equal 4", 4, power(2,2));
    assert_equal_numbers("2 ^ 1 should equal 2", 2, power(2,1));
    assert_equal_numbers("2 ^ 0 should equal 1", 1, power(2,0));
}

void
test_factorial() {
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
```
**Step 3**:
Run the program!
```bash
Tests found: 3
✔ Factorial testing
✘ Power testing
    2 ^ 0 should equal 1: expected 1 but got 2
✔ String testing
```
