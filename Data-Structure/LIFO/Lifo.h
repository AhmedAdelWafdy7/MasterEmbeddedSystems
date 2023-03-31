#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int length;
    unsigned int count;
    unsigned char* base;
    unsigned char* head;
}lifo_buf_t;

typedef enum {
    LIFO_NO_ERROR,
    LIFO_FULL,
    LIFO_NOT_FULL,
    LIFO_EMPTY,
    LIFO_NOT_EMPTY,
    LIFO_NULL
}lifo_status;

lifo_status lifo_push_item(lifo_buf_t* buf,unsigned char item);
lifo_status lifo_pop_item(lifo_buf_t* buf,unsigned char *item);
