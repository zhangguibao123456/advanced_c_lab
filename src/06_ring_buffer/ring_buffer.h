#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct RingBuffer {
    uint8_t *data;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t size;
} RingBuffer;

void rb_init(RingBuffer *rb, uint8_t *storage, size_t capacity);
int rb_push(RingBuffer *rb, uint8_t byte);
int rb_pop(RingBuffer *rb, uint8_t *out_byte);
size_t rb_write(RingBuffer *rb, const uint8_t *data, size_t count);
size_t rb_read(RingBuffer *rb, uint8_t *out, size_t count);
size_t rb_size(const RingBuffer *rb);
size_t rb_free(const RingBuffer *rb);

#endif
