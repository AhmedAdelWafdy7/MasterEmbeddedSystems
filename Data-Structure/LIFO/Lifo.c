#include "Lifo.h"

lifo_status lifo_is_full(lifo_buf_t* buf){
    if(!buf || !buf->head || !buf->base){
        return LIFO_NULL;
    }
    if(buf->count == buf->length){
        return LIFO_FULL;
    }
    else{
        return LIFO_NOT_FULL;
    }
}


lifo_status lifo_is_empty(lifo_buf_t* buf){
    if(!buf || !buf->head || !buf->base){
        return LIFO_NULL;
    }
    if(buf->base == buf->head){
        return LIFO_EMPTY;
    }
    else{
        return LIFO_NOT_EMPTY;
    }
}

lifo_status lifo_push_item(lifo_buf_t* buf,unsigned char item){
    if(!buf || !buf->head || !buf->base){
        return LIFO_NULL;
    }
    if(lifo_is_full(buf) == LIFO_FULL){
        return LIFO_NULL;
    }
    *(buf->head) = item;
    buf->head++;
    buf->count++;
    return LIFO_NO_ERROR;

}

lifo_status lifo_pop_item(lifo_buf_t* buf,unsigned char *item){
    if(!buf || !buf->head || !buf->base){
        return LIFO_NULL;
    }
    if(lifo_is_empty(buf) == LIFO_EMPTY){
        return LIFO_NULL;
    }
    buf->head--;
    *item = *(buf->head);
    buf->count--;
    return LIFO_NO_ERROR;
}