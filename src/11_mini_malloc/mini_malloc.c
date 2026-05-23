#include "mini_malloc.h"

#include <stdint.h>

static size_t align8(size_t value) {
    return (value + 7U) & ~7U;
}

void mini_heap_init(MiniHeap *heap, void *memory, size_t capacity) {
    heap->memory = memory;
    heap->capacity = capacity;
    heap->first = (MiniBlock *)memory;
    heap->first->size = capacity - sizeof(MiniBlock);
    heap->first->free = 1;
    heap->first->next = 0;
}

void *mini_malloc(MiniHeap *heap, size_t size) {
    const size_t wanted = align8(size);
    for (MiniBlock *block = heap->first; block != 0; block = block->next) {
        if (!block->free || block->size < wanted) {
            continue;
        }

        const size_t remaining = block->size - wanted;
        if (remaining > sizeof(MiniBlock) + 8U) {
            unsigned char *next_addr = (unsigned char *)(block + 1) + wanted;
            MiniBlock *next = (MiniBlock *)next_addr;
            next->size = remaining - sizeof(MiniBlock);
            next->free = 1;
            next->next = block->next;
            block->next = next;
            block->size = wanted;
        }

        block->free = 0;
        return block + 1;
    }
    (void)heap;
    return 0;
}

void mini_free(MiniHeap *heap, void *ptr) {
    (void)heap;
    if (ptr == 0) {
        return;
    }
    MiniBlock *block = (MiniBlock *)ptr - 1;
    block->free = 1;

    while (block->next != 0 && block->next->free) {
        block->size += sizeof(MiniBlock) + block->next->size;
        block->next = block->next->next;
    }
}

size_t mini_free_bytes(const MiniHeap *heap) {
    size_t total = 0;
    for (const MiniBlock *block = heap->first; block != 0; block = block->next) {
        if (block->free) {
            total += block->size;
        }
    }
    return total;
}
