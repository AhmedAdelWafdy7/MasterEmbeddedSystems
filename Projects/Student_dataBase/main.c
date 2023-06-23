/**
 * Main File
 * Ahmed Adel Wafdy
*/
#include "FIFO.h"
#include "StudentDB.h"
int main(){
    	uint32_t choice;
  do {
        printf("\nStudent Database Menu:\n");
	    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		printf("Choose an Option from list to do:        \n");
	    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		printf("1 : Add the student details from file    \n");
		printf("2 : Add the student details Manually     \n");
		printf("3 : Find the Student by given Roll number\n");
		printf("4 : Find the Student by given First name \n");
		printf("5 : Find the Student by registered course\n");
		printf("6 : Find the length                      \n");
		printf("7 : Delete student                       \n");
		printf("8 : Update student                       \n");
		printf("9 : View students                        \n");
		printf("10: Save the list and Exit               \n");
	    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

		printf("Enter a choice: ");
		scanf( "%d" , &choice );

		//switching an option
		switch (choice){
		case 1:
			Add_Student_From_File();
			break;
		case 2:
			Add_Student_Manually();
			break;
		case 3:
			Find_Student_Using_RollNumber();
			break;
		case 4:
			Find_Student_Using_FirstName();
			break;
		case 5:
			Find_Student_Using_CourseID();
			break;
		case 6:
			Find_Length();
			break;
		case 7:
			Detete_Student();
			break;
		case 8:
			Update_Student();
			break;
		case 9:
			View_Students();
			break;
		case 10:
			Save_to_File();
			break;
		default:
			printf("A very bad Choice\n");
			break;
		}
	}while (choice != 10);
}
