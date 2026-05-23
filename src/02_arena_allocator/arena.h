#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena {
    unsigned char *buffer;
    size_t capacity;
    size_t offset;
} Arena;

void arena_init(Arena *arena, void *buffer, size_t capacity);
void *arena_alloc(Arena *arena, size_t size, size_t alignment);
void arena_reset(Arena *arena);

#endif
