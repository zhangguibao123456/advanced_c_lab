#include "ring_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    uint8_t storage[8];
    RingBuffer rb;
    rb_init(&rb, storage, sizeof(storage));

    const uint8_t first[] = {'A', 'B', 'C', 'D', 'E'};
    if (rb_write(&rb, first, sizeof(first)) != sizeof(first)) {
        return EXIT_FAILURE;
    }

    uint8_t out[8] = {0};
    if (rb_read(&rb, out, 3) != 3 || memcmp(out, "ABC", 3) != 0) {
        return EXIT_FAILURE;
    }

    const uint8_t second[] = {'F', 'G', 'H', 'I', 'J', 'K'};
    const size_t written = rb_write(&rb, second, sizeof(second));
    if (written != 6 || rb_size(&rb) != 8 || rb_free(&rb) != 0) {
        return EXIT_FAILURE;
    }

    memset(out, 0, sizeof(out));
    if (rb_read(&rb, out, sizeof(out)) != sizeof(out) || memcmp(out, "DEFGHIJK", 8) != 0) {
        return EXIT_FAILURE;
    }

    printf("ring buffer ok\n");
    return EXIT_SUCCESS;
}
