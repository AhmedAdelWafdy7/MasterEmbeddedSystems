#ifndef _STUDENT_DATA_BASE_
#define _STUDENT_DATA_BASE_


#include <stdio.h>



struct SData{
    int id;
    char name[40];
    float height;
};

struct SStudent{
    struct SData Student;
    struct SStudent *PNextStudent;
};

struct SStudent *gpFirstStudent = NULL;
void fill_the_record(struct SStudent* new_student)
{
    char temp_text[40];

}

#endif