#include "ring_buffer.h"

void rb_init(RingBuffer *rb, uint8_t *storage, size_t capacity) {
    rb->data = storage;
    rb->capacity = capacity;
    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;
}

int rb_push(RingBuffer *rb, uint8_t byte) {
    if (rb->size == rb->capacity) {
        return 0;
    }
    rb->data[rb->head] = byte;
    rb->head = (rb->head + 1U) % rb->capacity;
    rb->size++;
    return 1;
}

int rb_pop(RingBuffer *rb, uint8_t *out_byte) {
    if (rb->size == 0) {
        return 0;
    }
    *out_byte = rb->data[rb->tail];
    rb->tail = (rb->tail + 1U) % rb->capacity;
    rb->size--;
    return 1;
}

size_t rb_write(RingBuffer *rb, const uint8_t *data, size_t count) {
    size_t written = 0;
    while (written < count && rb_push(rb, data[written])) {
        written++;
    }
    return written;
}

size_t rb_read(RingBuffer *rb, uint8_t *out, size_t count) {
    size_t read = 0;
    while (read < count && rb_pop(rb, &out[read])) {
        read++;
    }
    return read;
}

size_t rb_size(const RingBuffer *rb) {
    return rb->size;
}

size_t rb_free(const RingBuffer *rb) {
    return rb->capacity - rb->size;
}
