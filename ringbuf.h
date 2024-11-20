#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// 环形缓冲区结构体
typedef struct {
    uint8_t *buffer;    // 数据缓冲区
    size_t size;        // 缓冲区总大小
    size_t head;        // 写指针
    size_t tail;        // 读指针
} ringbuf_t;

/**
 * 初始化环形缓冲区
 * @param rb 指向环形缓冲区结构体
 * @param buffer 数据缓冲区
 * @param size 缓冲区大小
 */
void ringbuf_init(ringbuf_t *rb, uint8_t *buffer, size_t size);

/**
 * 向环形缓冲区写入数据
 * @param rb 指向环形缓冲区结构体
 * @param data 要写入的数据指针
 * @param length 写入的数据长度
 * @return 实际写入的数据长度
 */
size_t ringbuf_write(ringbuf_t *rb, const uint8_t *data, size_t length);

/**
 * 从环形缓冲区读取数据
 * @param rb 指向环形缓冲区结构体
 * @param data 读取数据存放的缓冲区
 * @param length 要读取的数据长度
 * @return 实际读取的数据长度
 */
size_t ringbuf_read(ringbuf_t *rb, uint8_t *data, size_t length);

/**
 * 获取环形缓冲区中的数据大小
 * @param rb 指向环形缓冲区结构体
 * @return 数据大小
 */
size_t ringbuf_data_size(const ringbuf_t *rb);

/**
 * 检查缓冲区是否已满
 * @param rb 指向环形缓冲区结构体
 * @return true: 缓冲区满; false: 缓冲区未满
 */
bool ringbuf_is_full(const ringbuf_t *rb);

/**
 * 检查缓冲区是否为空
 * @param rb 指向环形缓冲区结构体
 * @return true: 缓冲区空; false: 缓冲区非空
 */
bool ringbuf_is_empty(const ringbuf_t *rb);

#endif // RINGBUF_H
