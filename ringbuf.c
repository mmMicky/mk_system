#include "ringbuf.h"
#include <string.h>

void ringbuf_init(ringbuf_t *rb, uint8_t *buffer, size_t size) {
    rb->buffer = buffer;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
}

size_t ringbuf_write(ringbuf_t *rb, const uint8_t *data, size_t length) {
    size_t bytes_written = 0;
    for (size_t i = 0; i < length; i++) {
        if (ringbuf_is_full(rb)) {
            break; // 缓冲区满，停止写入
        }
        rb->buffer[rb->head] = data[i];
        rb->head = (rb->head + 1) % rb->size;
        bytes_written++;
    }
    return bytes_written;
}

size_t ringbuf_read(ringbuf_t *rb, uint8_t *data, size_t length) {
    size_t bytes_read = 0;
    for (size_t i = 0; i < length; i++) {
        if (ringbuf_is_empty(rb)) {
            break; // 缓冲区空，停止读取
        }
        data[i] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % rb->size;
        bytes_read++;
    }
    return bytes_read;
}

size_t ringbuf_data_size(const ringbuf_t *rb) {
    if (rb->head >= rb->tail) {
        return rb->head - rb->tail;
    } else {
        return rb->size - (rb->tail - rb->head);
    }
}

bool ringbuf_is_full(const ringbuf_t *rb) {
    return ((rb->head + 1) % rb->size) == rb->tail;
}

bool ringbuf_is_empty(const ringbuf_t *rb) {
    return rb->head == rb->tail;
}
