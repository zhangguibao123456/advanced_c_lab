#ifndef MINI_MALLOC_H
#define MINI_MALLOC_H

#include <stddef.h>

typedef struct MiniBlock {
    size_t size;
    int free;
    struct MiniBlock *next;
} MiniBlock;

typedef struct MiniHeap {
    unsigned char *memory;
    size_t capacity;
    MiniBlock *first;
} MiniHeap;

void mini_heap_init(MiniHeap *heap, void *memory, size_t capacity);
void *mini_malloc(MiniHeap *heap, size_t size);
void mini_free(MiniHeap *heap, void *ptr);
size_t mini_free_bytes(const MiniHeap *heap);

#endif
