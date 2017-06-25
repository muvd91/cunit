# cunit

**Step 1**: 
Include cunit.h and register your test.
```c
#include "cunit.h"
int                                            
main() {
    test("Factorial testing", &test_factorial);
    print_results();
    return 0;
}
```
**Step 2**: 
Test your code through the use of asserts
```c
void                                                               
test_factorial() {
    assert_equals_number("5! should equal 120", 120, factorial(5));
    assert_equals_number("4! should equal 24", 24, factorial(4));
    assert_equals_number("3! should equal 6", 6, factorial(3));
    assert_equals_number("2! should equal 2", 2, factorial(2));
    assert_equals_number("1! should equal 1", 1, factorial(1));
}
```
**Step 3**:
Run the program!
```bash
./example
Tests found: 1
'
```
