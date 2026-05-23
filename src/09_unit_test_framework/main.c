#include "mini_test.h"

static int clamp(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

int main(void) {
    TestRunner runner;
    test_init(&runner);

    test_expect_int(&runner, "clamp below", 0, clamp(-3, 0, 10));
    test_expect_int(&runner, "clamp inside", 7, clamp(7, 0, 10));
    test_expect_int(&runner, "clamp above", 10, clamp(99, 0, 10));

    return test_finish(&runner);
}
