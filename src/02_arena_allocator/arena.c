#include "arena.h"

#include <stdint.h>

static size_t align_forward(size_t value, size_t alignment) {
    const size_t mask = alignment - 1U;
    return (value + mask) & ~mask;
}

void arena_init(Arena *arena, void *buffer, size_t capacity) {
    arena->buffer = buffer;
    arena->capacity = capacity;
    arena->offset = 0;
}

void *arena_alloc(Arena *arena, size_t size, size_t alignment) {
    if (alignment == 0 || (alignment & (alignment - 1U)) != 0U) {
        return 0;
    }

    const uintptr_t base = (uintptr_t)arena->buffer;
    const size_t aligned = align_forward((size_t)(base + arena->offset), alignment);
    const size_t next_offset = aligned - (size_t)base + size;
    if (next_offset > arena->capacity) {
        return 0;
    }

    arena->offset = next_offset;
    return (void *)aligned;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}
