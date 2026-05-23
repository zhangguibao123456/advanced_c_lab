#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *copy_message(const char *text) {
    const size_t len = strlen(text);
    char *copy = malloc(len + 1U);
    if (copy == 0) {
        return 0;
    }
    memcpy(copy, text, len + 1U);
    return copy;
}

static int sum_owned_array(void) {
    int *values = calloc(4U, sizeof(values[0]));
    if (values == 0) {
        return -1;
    }

    for (int i = 0; i < 4; ++i) {
        values[i] = (i + 1) * 10;
    }

    int total = 0;
    for (int i = 0; i < 4; ++i) {
        total += values[i];
    }

    free(values);
    return total;
}

int main(void) {
    char *message = copy_message("owned memory");
    if (message == 0) {
        return EXIT_FAILURE;
    }

    printf("%s total=%d\n", message, sum_owned_array());
    free(message);

    puts("Try: valgrind --leak-check=full ./build/08_memory_bugs");
    return EXIT_SUCCESS;
}
