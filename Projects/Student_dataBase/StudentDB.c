/**
 * StudentDB.c
 * Ahmed Adel Wafdy
*/

#include "StudentDB.h"
#include "FIFO.h"

uint8_t str[20];
uint8_t count =0 ,temp;
#define Student_buffer_length       5

FIFO_buf_t fifo_student;
Student_t student_buffer[Student_buffer_length];
FILE* stud_file,*list;

Student_t new_student;

Status_t view_student(Student_t * fifo_buf){
    printf("Student ROLL Number :%d\n",fifo_buf->Num);
    printf("Student NAME :%s %s\n",fifo_buf->First_name,fifo_buf->Last_name);
    printf("Student ROLL Number :%f\n",fifo_buf->GPA);
    for(uint32_t i=0; i<4;i++){
        printf("Student Courses ID =%d\n",fifo_buf->ID[i]);
    }
    return DONE;
}
Status_t roll_searcher(uint8_t ID ,uint8_t count){
    for(uint32_t i=0;i<count;i++){
        if(student_buffer[i].Num == ID){
            printf("[ERROR] ROLL number %d is for another student",ID);
            printf("[ERROR] TRY another student",ID);
            return ERROR;
        }
    }
    return NOERROR;
}

Status_t add_student_from_file(){
    // I will uswe fopen() to open file
    stud_file = fopen("data.txt","r");
    
    //validate if file opened or not 
    if(stud_file == NULL){
        printf("[ERROR] data.txt isn't found====> adding students failed \n");
        return ERROR;
    }

    //loop for file
    while(!feof(stud_file)){
        fscanf(stud_file,"%d", &new_student.Num);
        if(roll_searcher(new_student.Num,count) == ERROR){
            //skip line
            fsccanf(stud_file,"%*[^\n]");
            continue;
        }
        //read&store names of student
        fscanf(stud_file,"%s",&new_student.First_name);
        fscanf(stud_file,"%s",&new_student.Last_name);
        fscanf(stud_file,"%f",&new_student.GPA);
        for(uint32_t i =0 ; i<4 ; i++){
            fscanf(stud_file,"%d",&new_student.ID[i]);
        }

        //storing
        if(count ==0){
            if(fifo_init(&fifo_student,student_buffer,Student_buffer_length) == FIFO_NO_ERROR){
                printf("[DONE] Student Initialzation is done");
            }
            if(fifo_enqueue(&fifo_student,new_student) == FIFO_NO_ERROR){
                printf("[DONE] Student Enqueue is done");
            }
            else{
                printf("[ERROR] ERROR happened in Enqueue");
                return ERROR;
            }
            count++;
        
        }
    }
    printf("Students Data are stored Successfully");
    fclose(stud_file);
    printf("[Done]\n");
    return DONE;
}
Status_t add_student_manual(){
    if(count == 0){
        if(fifo_init(&fifo_student,student_buffer,Student_buffer_length) == 0){
            printf("[NO ERROR] FIFO STUDENT Inintialzation Done\n");
        }
    }
    printf("Student ROLL Number: ");
    scanf("%d",&temp);

    if(roll_searcher(temp,count) == ERROR){
        return ERROR;
    }
    else{
        new_student.Num = temp;
    }

    printf("Student First Name: ");
    scanf("%s",new_student.First_name);
    printf("Student Last Name: ");
    scanf("%s",new_student.Last_name);

    printf("Student GPA: ");
    scanf("%f",&(new_student.GPA));
	printf("Math4 ID course is  1\n");
	printf("Logical Circuits ID course is     2\n");
	printf("Electrical Measurment course is  3\n");
	printf("Sensors course is  4\n");
	printf("Ethics course is    5\n");
	printf("Electrical Circuits1 course is     6\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

	printf("Courses are \n");
	for ( uint32_t i=0 ; i<4 ; i++ )
	{
		printf("ID Course %d: ", i );
		scanf( "%d" , &new_student.ID[i] );
	}

    if(fifo_enqueue(&fifo_student,new_student) == FIFO_NO_ERROR){
        printf("FIFO NO ERROR IN ENQUEUE \n");
    } 
    else{
        printf("FIFO ERROR IN ENQUEUE \n");
        return ERROR;
    }
    count++;
    return DONE;   
}

Status_t delete_student(){
	//FIFO Student isn't empty?
	if ( FIFO_STATUS( &fifo_student ) == FIFO_EMPTY )
		return FIFO_EMPTY;

	//Read the roll number 
	printf("Student Roll Number: ");
	scanf( "%d" , &temp );

	fifo_student.tail = student_buffer;

	for ( uint32_t i = 0 ; i < fifo_student.count ; i++ )
	{
		if ( student_buffer[i].Num == temp )
		{
			printf("This Roll Number %d is for Student: \n", temp);
			View_Student( student_buffer + i );
			printf("Are you sure that you wanna delete him (Yes or No) ?\n");
			scanf( "%s" , str );

			if ( stricmp( str , "No" ) == 0 )
				return DONE;

			student_buffer[i] = *(fifo_student.tail);

			if( fifo_student.tail == fifo_student.base )
			{
				fifo_student.tail++;
				fifo_student.base = fifo_student.tail;
			}

			fifo_student.count--;

			printf("[DONE]\n");
			return DONE;
		}

		fifo_student.tail++;
	}

	printf("This Roll Number isn't found  in the list\n");

	return DONE;
}
Status_t update_student(){
	printf("Enter student Roll Number: ");
	scanf( "%d" , &temp );

	fifo_student.tail = student_buffer;

	for ( uint32_t i=0 ; i<fifo_student.count ; i++ )
	{
		if ( fifo_student.tail->Num == temp )
		{
			printf("This Roll Number %d is for Student: \n", temp);
			View_Student( student_buffer + i );

			printf("For update Student name select 1\n");
			printf("For update roll number select 2\n");
			printf("For update Student GPA select 3\n");
			printf("For update courses ID select 4\n");

			scanf( "%d" , &temp );

			switch(temp){
			case 1:
			{
				//read Student First Name
				printf("Student First Name: ");
				scanf( "%s" , str );
				strcpy( fifo_student.tail->First_name , str );

				//read Student First Name
				printf("Student Last Name: ");
				scanf( "%s" , str );
				strcpy( fifo_student.tail->Last_name , str );

				printf("[DONE]\n");
				return DONE;
			}
			case 2:
			{
				//read Student Roll Number
				printf("Student Roll Number: ");
				scanf( "%d" , &temp );
				fifo_student.tail->Num = temp;

				printf("[DONE]\n");
				return DONE;
			}
			case 3:
			{
				//read Student GPA
				printf("Student GPA: ");
				scanf( "%d" , &temp );
				fifo_student.tail->GPA = temp;

				printf("[DONE]\n");
				return DONE;
			}
			case 4:
			{
	            printf("Math4 ID course is  1\n");
	            printf("Logical Circuits ID course is     2\n");
	            printf("Electrical Measurment course is  3\n");
	            printf("Sensors course is  4\n");
	            printf("Ethics course is    5\n");
	            printf("Electrical Circuits1 course is     6\n");
	            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
				printf("Courses are \n");
				for ( uint32_t i=0 ; i<4 ; i++ )
				{
					printf("ID Course %d: ", i );
					scanf( "%d" , &temp );
					fifo_student.tail->ID[i] = temp;
				}

                printf("[DONE]\n");
				return DONE;
			}
			}
		}
		fifo_student.tail++;
	}

	printf("Roll Number isn't found  in the list\n");

	return DONE;
}
Status_t find_student_by_ID(){
	uint32_t Flag = 0;

	//Read Course ID
	printf("ID Course: ");
	scanf( "%d" , &temp );

	fifo_student.tail = student_buffer;

	for ( uint32_t i=0 ; i<fifo_student.count ; i++ )
	{
		printf("The Student who registered in %d are: \n", temp );
		for ( uint32_t j=0 ; j<4 ; j++ )
		{
			if ( student_buffer[i].ID[j] == temp )
			{
				Flag = 1;
				View_Student( student_buffer+i );
			}
			fifo_student.tail++;
		}
	}

	if (!Flag)
		printf("no one registered this course\n");

	printf("[DONE]\n");
	return DONE;
}
Status_t find_student_by_roll(){
	printf("Enter Student Roll Number: ");
    scanf( "%d" , &temp );

    fifo_student.tail = student_buffer;

	for ( uint32_t i=0 ; i<fifo_student.count ; i++ )
	{
		if ( fifo_student.tail->Num == temp )
		{
			printf("Roll Number %d is for Student: \n", temp);
			View_Student( student_buffer+i );

			printf("[DONE]\n");
			return DONE;
		}
		fifo_student.tail++;
	}

	printf("Roll Number isn't found  in the list\n");
	return FIFO_NO_ERROR;
}
Status_t find_student_by_name(){
  	uint32_t Flag = 0;

	printf("Enter student First Name: ");
	scanf( "%s" , str );

	fifo_student.tail = student_buffer;

	for ( uint32_t i=0 ; i<fifo_student.count ; i++ )
	{
		if ( stricmp( fifo_student.tail->First_name , str ) == 0 )
		{
			Flag = 1;
			printf("Name is for Student\n");
			View_Student( student_buffer+i );
		}
		fifo_student.tail++;
	}

    if (!Flag)
    	printf("This Name isn't found in the list\n");

    printf("[DONE]\n");
    return DONE;
}
Status_t find_length()
{
	printf("This list  %d Student\n", fifo_student.count );
	printf("[DONE]\n");
	return DONE;
}
Status_t view_students(){
	fifo_student.tail = student_buffer;
	for ( uint32_t i = 0; i < fifo_student.count; i++ )
	{
		if (( FIFO_STATUS(&fifo_student) != FIFO_EMPTY ) || (FIFO_STATUS(&fifo_student) != FIFO_NULL) )
		{
			View_Student(fifo_student.tail);
			fifo_student.tail++;
		}
		else
		{
			printf("FIFO Student is Empty\n");
			return FIFO_EMPTY;
		}
	}

	printf("[DONE]\n");
	return DONE;

}
Status_t save_to_file(){
	//Write file 
	list = fopen( "data.txt" , "w" );

	if ( list == NULL )
	{
		printf("[ERROR] data.txt file isn't found \n");
		printf("[ERROR] adding students from file failed. \n");
		return ERROR;
	}

	fifo_student.tail = student_buffer;

	//Until Student FIFO end
	for ( uint32_t i=0 ; i<fifo_student.count ; i++ )
	{
		fprintf( list , "%d " , fifo_student.tail->Num );
		fprintf( list , "%s " , fifo_student.tail->First_name );
		fprintf( list , "%s " , fifo_student.tail->Last_name );
		fprintf( list , "%f " , fifo_student.tail->GPA );

		for ( uint32_t i=0 ; i<4 ; i++ )
		{
			fprintf( list , "%d " , fifo_student.tail->ID[i] );
		}
		fprintf( list ,"\n");

		fifo_student.tail++;
	}
	printf("Students details are saved successfully\n");

	fclose(list);

	return DONE;
}
