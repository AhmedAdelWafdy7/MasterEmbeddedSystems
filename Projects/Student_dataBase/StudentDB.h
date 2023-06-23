/**
 * StudentDB.h
 * Ahmed Adel Wafdy
*/
#ifndef _SDB_H_
#define _SDB_H_


/*--------------------------Includes---------------------------*/
#include "FIFO.h"
#include <stdio.h>
#include "string.h"
#include "stdint.h"
/*--------------------------Data Types---------------------------*/

typedef enum{
    DONE,
    ERROR,
    NOERROR,
    EMPTY
}Status_t;
/*--------------------------APIS---------------------------*/
Status_t view_student(Student_t * fifo_buf);
Status_t roll_searcher(uint8_t ID ,uint8_t count);

Status_t add_student();
Status_t add_student_manual();

Status_t delete_student();
Status_t update_student();
Status_t find_student_by_ID();
Status_t find_student_by_roll();
Status_t find_student_by_name();
Status_t find_length();
Status_t view_students();
Status_t save_to_file();


#endif