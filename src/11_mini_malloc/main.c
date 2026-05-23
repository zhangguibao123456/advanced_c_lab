#include "mini_malloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    unsigned char memory[256];
    MiniHeap heap;
    mini_heap_init(&heap, memory, sizeof(memory));

    char *name = mini_malloc(&heap, 32);
    int *values = mini_malloc(&heap, 4U * sizeof(values[0]));
    if (name == 0 || values == 0) {
        return EXIT_FAILURE;
    }

    strcpy(name, "mini heap");
    for (int i = 0; i < 4; ++i) {
        values[i] = i + 1;
    }

    mini_free(&heap, values);
    mini_free(&heap, name);

    printf("free=%zu\n", mini_free_bytes(&heap));
    return mini_free_bytes(&heap) >= 200U ? EXIT_SUCCESS : EXIT_FAILURE;
}
