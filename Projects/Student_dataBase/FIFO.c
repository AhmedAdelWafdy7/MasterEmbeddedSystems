#include "FIFO.h"

FIFO_status fifo_init(FIFO_buf_t* fifo,Student_t* buff,uint32_t buff_length){
    fifo->base = buff;
    fifo->head = fifo->base;
    fifo->tail = fifo->base;
    fifo->length = buff_length;
    fifo->count = 0;
    if(fifo->base && fifo->length)
        return FIFO_NO_ERROR;
    else
        return FIFO_NULL;    
}
FIFO_status fifo_is_buf_full(FIFO_buf_t* fifo){
    //check if fifo is exit 
    if(!fifo->base || !fifo->head || !fifo->tail)
        return FIFO_NULL;
    if(fifo->count >= fifo->length)
        printf("fifo is full !!!!");
        return FIFO_FULL;

    return FIFO_NO_ERROR;    
}
FIFO_status fifo_enqueue(FIFO_buf_t* fifo,Student_t ENQ_Data){
    if( fifo_is_buf_full(fifo) == FIFO_NO_ERROR){
		if( fifo->tail != fifo->base )
			fifo->head = fifo->base;

		*(fifo->head) = ENQ_Data ;
		fifo->head++;
		fifo->count++;

		return FIFO_NO_ERROR;;        
    }
    else{
        printf("Enqueue Failed\n");
        return (fifo_is_buf_full(fifo));
    }

}
FIFO_status fifo_dequeue(FIFO_buf_t* fifo,Student_t* DEQ_Data){
    //check if fifo is exist
    if(!fifo->base || !fifo->head ||!fifo->tail){
		if( fifo->tail == fifo->base + (fifo->length) * sizeof(FIFO_status) )
			fifo->tail = fifo->base;

		*DEQ_Data = *(fifo->tail);
		fifo->tail++;
		fifo->count--;

		return FIFO_NO_ERROR;
	}
	else
	{
		printf("FIFO Dequeue is failed\n");
		return FIFO_ERROR;
	}      
}

void fifo_print(FIFO_buf_t *fifo){
    element_type* temp;
    int i;
    if(fifo->count == 0){
        printf("FiFo is empty \n");
        return FIFO_EMPTY;
    }
    temp = fifo->tail;
    printf(" \n ============FIFO Print==========\n");
    for(i=0;i<fifo->count;i++){
        printf("\t %x \n",*temp);
        temp++;
    }
    printf("\n ======================= \n");
}

