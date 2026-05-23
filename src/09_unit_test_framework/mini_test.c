#include "mini_test.h"

#include <stdio.h>

void test_init(TestRunner *runner) {
    runner->passed = 0;
    runner->failed = 0;
}

void test_expect_int(TestRunner *runner, const char *name, int expected, int actual) {
    if (expected == actual) {
        runner->passed++;
        printf("[PASS] %s\n", name);
        return;
    }

    runner->failed++;
    printf("[FAIL] %s expected=%d actual=%d\n", name, expected, actual);
}

int test_finish(const TestRunner *runner) {
    printf("passed=%u failed=%u\n", runner->passed, runner->failed);
    return runner->failed == 0U ? 0 : 1;
}
