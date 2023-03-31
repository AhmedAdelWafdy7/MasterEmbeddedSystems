#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdio.h>
#include <stdint.h>

#define element_type uint8_t

typedef struct{
    unsigned int length;
    element_type *base;
    element_type* tail;
    element_type* head;
    unsigned int count;
}FIFO_buf_t;

typedef enum {
    FIFO_NO_ERROR,
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_NULL
}FIFO_status;

//FIFO APIs

FIFO_status fifo_enqueue(FIFO_buf_t* fifo,element_type* ENQ_Data);
FIFO_status fifo_dequeue(FIFO_buf_t* fifo,element_type* DEQ_Data);
FIFO_status fifo_is_buf_full(FIFO_buf_t* fifo);
void fifo_print(FIFO_buf_t *fifo);
FIFO_status fifo_init(FIFO_buf_t* fifo,element_type* buff,uint32_t buff_length);

#endif 