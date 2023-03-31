#include "Student_Data_Base.h"

void fill_the_record(struct SStudent* new_student)
{
    char temp_text[40];
    DPRINTF("\n Enter the ID : ");
    gets(temp_text);
    new_student->Student.id = atoi (temp_text);

    DPRINTF("\n Enter the Full Name : ");
    gets(new_student->Student.name);    

    DPRINTF("\n Enter the height : ");
    gets(temp_text);
    new_student->Student.height= atoi (temp_text);

}

void AddStudent(){
    struct SStudent *pLastStudent;
    struct SStudent* pNewStudent;
    if(gpFirstStudent == NULL)
    {
        //create the first record 
        pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
        //assign the gpFirstStudent to it
        gpFirstStudent = pNewStudent;
    }
    else{
        //navigate until reach the last record 
        pLastStudent = gpFirstStudent;
        While(pLastStudent->PNextStudent)
            pLastStudent = pLastStudent->pNextStudent;
        //CREATE NEW RECORD AND ASSIGN PNEXT TO it
        pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
        pLastStudent->PNextStudent = pNewStudent;
    }
    // fill the new record 
    fill_the_record(pNewStudent);
    //set the next record to null
    pNewStudent->PNextStudent = NULL;
}

int Delete_student(){
    char temp_text[40];
    int i, selected_id;
    //Geet Selected recorded Id from user
    DPRINTF("\n Enter Student ID to be Deleted : ");
    gets(temp_text);
    selected_id = atoi(temp_text);
    if(gpFirstStudent) //list have a records
    {
        struct SStudent* pPreviousStudent = NULL;
        struct SStudent* pSelectedStudent = gpFirstStudent;
        while(pSelectedStudent){
            //compare the recorded ID with the selected id
            if(pSelectedStudent->Student.id == selected_id){
                if(pPreviousStudent){
                    pPreviousStudent->PNextStudent = pSelectedStudent->PNextStudent;
                }
                else{
                    gpFirstStudent = pSelectedStudent->PNextStudent;
                }
                free(pSelectedStudent);
                return 1;
            }
            //store previous record pointer
            pPreviousStudent = pSelectedStudent;
            pSelectedStudent = pSelectedStudent->PNextStudent;
        }
    }
    DPRINTF("\n can't find student id ");
    return 0;
}

void view_students(){
    int count = 0;
    struct SStudent* PCurrentStudent = gpFirstStudent;
    if(!gpFirstStudent)
        DPRINTF("\n Empty List");

    while(PCurrentStudent){
        DPRINTF("\n Record Number %d",count+1);
        DPRINTF("\n ID: %d",PCurrentStudent->Student.id);
        DPRINTF("\n Name : %s",PCurrentStudent->Student.name);
        DPRINTF("\n Height : %f",PCurrentStudent->Student.height);
        PCurrentStudent = PCurrentStudent->PNextStudent;
        count++;
    }    
}
void Delete_all(){
    struct SStudent* PCurrentStudent = gpFirstStudent;
    if(!gpFirstStudent){
        DPRINTF("/n Empty List");
    }
    While(PCurrentStudent){
        struct SStudent* pTempStudent = PCurrentStudent;
        PCurrentStudent = PCurrentStudent->PNextStudent;
        free(pTempStudent);
    }
    gpFirstStudent = NULL;
}