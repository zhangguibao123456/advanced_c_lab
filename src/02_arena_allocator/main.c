#include "arena.h"

#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Sample {
    int id;
    double value;
} Sample;

int main(void) {
    unsigned char storage[256];
    Arena arena;
    arena_init(&arena, storage, sizeof(storage));

    Sample *samples = arena_alloc(&arena, 4U * sizeof(samples[0]), alignof(Sample));
    if (samples == 0) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 4; ++i) {
        samples[i].id = i + 1;
        samples[i].value = 10.0 * (double)(i + 1);
    }

    for (int i = 0; i < 4; ++i) {
        printf("sample[%d]=%.1f\n", samples[i].id, samples[i].value);
    }

    arena_reset(&arena);
    return arena.offset == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
