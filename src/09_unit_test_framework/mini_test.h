#ifndef MINI_TEST_H
#define MINI_TEST_H

typedef struct TestRunner {
    unsigned passed;
    unsigned failed;
} TestRunner;

void test_init(TestRunner *runner);
void test_expect_int(TestRunner *runner, const char *name, int expected, int actual);
int test_finish(const TestRunner *runner);

#endif
