#include <stdio.h>
#include <stdlib.h>

typedef int (*CompareFn)(const void *left, const void *right);

static int compare_int_ascending(const void *left, const void *right) {
    const int a = *(const int *)left;
    const int b = *(const int *)right;
    return (a > b) - (a < b);
}

static int sum_with_cursor(const int *begin, const int *end) {
    int total = 0;
    for (const int *it = begin; it != end; ++it) {
        total += *it;
    }
    return total;
}

static void sort_ints(int *items, size_t count, CompareFn compare) {
    qsort(items, count, sizeof(items[0]), compare);
}

int main(void) {
    int values[] = {42, 7, 13, -4, 99, 0};
    const size_t count = sizeof(values) / sizeof(values[0]);

    sort_ints(values, count, compare_int_ascending);

    for (size_t i = 0; i < count; ++i) {
        printf("%d%s", values[i], i + 1 == count ? "\n" : " ");
    }

    const int total = sum_with_cursor(values, values + count);
    printf("sum=%d\n", total);
    return total == 157 ? EXIT_SUCCESS : EXIT_FAILURE;
}
