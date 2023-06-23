#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdio.h>
#include <stdint.h>

#define element_type uint8_t
typedef struct {
	float GPA;
	uint8_t First_name[20];
	uint8_t Last_name[20];
	uint32_t Num;
	uint32_t ID[4];
} Student_t;
typedef struct{
    unsigned int length;
    Student_t *base;
    Student_t* tail;
    Student_t* head;
    unsigned int count;
}FIFO_buf_t;

typedef enum {
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_NULL,
    FIFO_NO_ERROR,
    FIFO_ERROR
}FIFO_status;

//FIFO APIs

FIFO_status fifo_enqueue(FIFO_buf_t* fifo,Student_t ENQ_Data);
FIFO_status fifo_dequeue(FIFO_buf_t* fifo,Student_t* DEQ_Data);
FIFO_status fifo_is_buf_full(FIFO_buf_t* fifo);
void fifo_print(FIFO_buf_t *fifo);
FIFO_status fifo_init(FIFO_buf_t* fifo,Student_t* buff,uint32_t buff_length);

#endif 