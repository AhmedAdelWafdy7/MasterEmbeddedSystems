/*
 * Scheduler.c
 *
 *  Created on: Aug 2, 2023
 *      Author: Ahmed Adel Wafdy
 */


#include "Scheduler.h"
#include "My_RTOS_FIFO.h"
struct {
	Task_ref* OSTasks[100]; //Sch. Table
	unsigned int _S_MSP_Task ;
	unsigned int _E_MSP_Task ;
	unsigned int PSP_Task_Locator ;
	unsigned int NoOfActiveTasks ;
	Task_ref* CurrentTask ;
	Task_ref* NextTask ;
	enum{
		OSsuspend,
		OsRunning
	}OSmodeID;
}OS_Control;

typedef enum {
	SVC_Activatetask,
	SVC_terminateTask,
	SVC_TaskWaitingTime,
	SVC_AquireMutex,
	SVC_ReleaseMutex
}SVC_ID;

FIFO_Buf_t Ready_QUEUE ;

Task_ref* Ready_QUEUE_FIFO[100] ;
Task_ref MYRTOS_idleTask ;



__attribute ((naked)) void PendSV_Handler()
{
	//save context of Current task
	//get current task PSP from CPU registers XPSR ---> r0
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

	//using this Current_PSP (Pointer) tp store (R4 to R11)
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r4 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r5 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r6 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r7 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r8 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r9 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r10 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r11 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );

	//save Current value of PSP
	//Restore Context of the nexxt stack


	if (OS_Control.NextTask != NULL){
	OS_Control.CurrentTask = OS_Control.NextTask ;
	OS_Control.NextTask = NULL ;
	}

	__asm volatile("mov r11,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r10,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r9,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r8,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r7,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r6,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r5,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r4,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;

	//update PSP and exit
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	__asm volatile("BX LR");

}



unsigned char IdleTaskLed ;
void MYRTOS_IdleTask()
{

	// wfe ===> wait for interrupt used to make interrupt in low power mode until interrupt received

	while(1)
	{
		IdleTaskLed ^= 1 ;
		__asm("wfe");
	}

}



void MYRTOS_Create_MainStack()
{
	OS_Control._S_MSP_Task = &_estack;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task - MainStackSize;
	 //Allign 8 bytes between Main Stack and PSP tasks

	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8);

	//if (_E_MSP_Task <&_eheap) Error:excedded the availble stack size
}

MYRTOS_errorID MYRTOS_init()
{
	MYRTOS_errorID error = NoError ;

	//update Os if susbended
	OS_Control.OSmodeID = OSsuspend ;

	//specify main stack for OS
	MYRTOS_Create_MainStack();

	//create OS ready queue
	if (FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) !=FIFO_NO_ERROR)
	{
		error += Ready_Queue_init_error ;
	}

	//Configure IDLE TASK
	strcpy (MYRTOS_idleTask.TaskName, "idleTask");
	MYRTOS_idleTask.priority = 255 ;
	MYRTOS_idleTask.p_TaskEntry = MYRTOS_IdleTask ;
	MYRTOS_idleTask.Stack_Size = 300 ;

	error += MYRTOS_CreateTask(&MYRTOS_idleTask);

	return error ;

}


void MyRTOS_Create_TaskStack(Task_ref* Tref)
{
	/*				-----------------
	 * 				_______XPSR______
	 * 				-----------------
	 * 				___PC____  ===> Next Task instruction Which Should be run
	 * 				-----------------
	 * 				___LR____ ===> return register which is saved in CPU while Task1 running before task Switching
	 * 				-----------------
	 * 				___r12____
	 * 				-----------------
	 * 				___r4___
	 * 				-----------------
	 * 				___r3____
	 * 				-----------------
	 * 				___r2____
	 * 				-----------------
	 * 				___r1____
	 * 				-----------------
	 * 				___r0____
	 * 				-----------------
	 * 				___	 *r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 * */
	Tref->Current_PSP = Tref->_S_PSP_Task ;

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = 0x01000000;    //XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = (unsigned int)Tref->p_TaskEntry ;  //PC ==> task entry


	Tref->Current_PSP-- ;  //LR ==> 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP
	*(Tref->Current_PSP)  = 0xFFFFFFFD ;

	for (int  j=0 ; j< 13 ; j++ )
	{
		Tref->Current_PSP-- ;
		*(Tref->Current_PSP)  = 0 ;

	}
}

MYRTOS_errorID MYRTOS_CreateTask(Task_ref* Tref)
{
	MYRTOS_errorID error = NoError ;

	// create it's own psp Stack;
	//check task stack size
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size ;
																			/*				-----------------
																			 * 				__S_PSP_TASK_____
																			 * 				-----------------
																			 * 				___Task_Stack____
																			 * 				-----------------
																			 * 				___E_PSP_TASK____
																			 *
																			 *
																			 * 				----------------
																			 * 				___HEAP_________
																			 *

																			 *
																			 * */

	if(Tref->_E_PSP_Task < (unsigned int)(&(_eheap)))
	{
		return Task_exceeded_StackSize ;
	}

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_Task_Locator = (Tref->_E_PSP_Task - 8);

	//Initialize PSP Task Stack
	MyRTOS_Create_TaskStack( Tref);

	//update sch Table
	OS_Control.OSTasks[OS_Control.NoOfActiveTasks]= Tref ;
	OS_Control.NoOfActiveTasks++ ;


	//Task State Update -> Suspend
	Tref->TaskState = Suspend ;

	return error ;

}

/*
 * ********************************************************
 * --------------------------------------------------------
 *
 * 					HANDLER MODE FUNCTIONS
 *
 * ********************************************************
 * --------------------------------------------------------
 */

/**===============================================
 * @Fn			- bubbleSort
 * @brief		- Bubble Sort is a simple sorting algorithm that repeatedly steps through the list to be sorted, compares adjacent elements, and swaps them if they are in the wrong order.
   	   	   	   	 The pass through the list is repeated until the list is sorted.
 	 	 	 	 It is named "Bubble Sort" because smaller elements "bubble" to the top of the list while larger elements "sink" to the bottom.
 * @retval		- void ====> none
 * Note			- none
 * */


void bubbleSort()
{
	unsigned int i, j , n;
	Task_ref* temp ;
	n = OS_Control.NoOfActiveTasks ;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (OS_Control.OSTasks[j]->priority > OS_Control.OSTasks[j + 1]->priority)
			{
				temp = OS_Control.OSTasks[j] ;
				OS_Control.OSTasks[j] = OS_Control.OSTasks[j + 1 ] ;
				OS_Control.OSTasks[j + 1] = temp ;
			}

}
void MyRTOS_Update_Schadule_tables()
{
	Task_ref* temp =NULL ;
	Task_ref* Ptask ;
	Task_ref* PnextTask ;
	int i = 0 ;

	//1- bubble sort SchTable OS_Control-> OSTASKS[100] (priority high then low)
	bubbleSort();
	//2- free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE, &temp /* pointer to pointer */)!=FIFO_EMPTY);

	//update Ready Queue
		// |
		// |-->	we will loop in active tasks in Scheduler after sorting it with bubble sort algorithm.
		// |--> set temperory task and next temprory task and put 3 Scenarios.
		//	  |--> if Ptask priority < next task
		//	  |--> if pTask priority equal to next task priority So we will go on round robin until one task of both terminate
		//	  |--> if Ptask priority > next task  (and it's not impossible after bubble sorting)
	while(i< OS_Control.NoOfActiveTasks)
	{
		Ptask = OS_Control.OSTasks[i] ;
		PnextTask = OS_Control.OSTasks[i+1] ;
		if (Ptask->TaskState != Suspend)
		{
			//in case we reached to the end of avaliable OSTASKS
			if (PnextTask->TaskState == Suspend)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = ready ;
				break ;
			}
			//	if the Ptask priority > nexttask then (lowest number is meaning higher priority)
			if (Ptask->priority < PnextTask->priority )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = ready ;
				break ;
			}else if (Ptask->priority == PnextTask->priority)
			{
				//	if the Ptask priority == nexttask then
				//		push Ptask to ready state
				//	And make the ptask = nexttask  and nexttask++
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = ready ;
			}else if (Ptask->priority > PnextTask->priority)
			{
				//not allowed to happen as we already reordered it by bubble sort
				break ;
			}
		}


		i++ ;
	}

}
/*
 * function Decide what next checks The Ready Queue if Empty and current task is susbended
 * 													|	|-->the Current Task set to be running and added back to the ready Queue
 * 													|		The next task is dequeued from the Ready Queue and setb to the running state
 * 													|>if the Current Task has the same priority as The next task
 * 														|--> added back to the ready queue and its state is set to ready
 * */
void Decide_whatNext()
{
	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if (Ready_QUEUE.counter == 0 && OS_Control.CurrentTask->TaskState != Suspend) //FIFO_EMPTY
	{
		OS_Control.CurrentTask->TaskState = Running ;
		//add the current task again(round robin)
		FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
		OS_Control.NextTask = OS_Control.CurrentTask ;
	}else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Control.NextTask);
		OS_Control.NextTask->TaskState = Running ;
		//update Ready queue (to keep round robin Algo. happen)
		if ((OS_Control.CurrentTask->priority == OS_Control.NextTask->priority )&&(OS_Control.CurrentTask->TaskState != Suspend))
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
			OS_Control.CurrentTask->TaskState = ready ;
		}
	}
}

//Handler Mode
void OS_SVC(int* Stack_Frame)
{
	//r0,r1,r2,r3,r12,LR,return address (PC) and XPSR
	unsigned char SVC_number ;
	SVC_number = *((unsigned char*)(((unsigned char*)Stack_Frame[6])-2)) ;

	switch (SVC_number)
	{
	case SVC_Activatetask:
	case SVC_terminateTask:
		//Update Sch Table, Ready Queue
		MyRTOS_Update_Schadule_tables();
		//OS is in Running State
		if (OS_Control.OSmodeID == OsRunning)
		{
			if (strcmp(OS_Control.CurrentTask->TaskName,"idleTask") != 0)
			{
				//Decide what Next
				Decide_whatNext();

				//trigger OS_pendSV (Switch Context/Restore)
				Trigger_OS_PENDSV();
			}
		}

		break;
	case SVC_TaskWaitingTime:
		MyRTOS_Update_Schadule_tables();


		break;
	}


}

/*
 * ********************************************************
 * --------------------------------------------------------
 *
 * 					THREAD MODE FUNCTIONS
 *
 * ********************************************************
 * --------------------------------------------------------
 */
MYRTOS_OS_SVC_Set(SVC_ID ID)
{
	switch (ID)
	{
	case SVC_Activatetask:
		__asm("svc #0x00");
		break;
	case SVC_terminateTask:
		__asm("svc #0x01");
		break;
	case SVC_TaskWaitingTime:
		__asm("svc #0x02");
		break;
	case SVC_AquireMutex:
		__asm("svc #0x03");  //Assignment Task
		break;
	case SVC_ReleaseMutex:
		__asm("svc #0x04"); //Assignment Task
		break;
	}
}

void MYRTOS_ActivateTask (Task_ref* Tref)
{
	Tref->TaskState = Waiting ;
	MYRTOS_OS_SVC_Set(SVC_Activatetask);
}
void MYRTOS_TerminateTask (Task_ref* Tref)
{
	Tref->TaskState = Suspend ;
	MYRTOS_OS_SVC_Set(SVC_terminateTask);
}
void MYRTOS_TaskWait(unsigned int NoTICKS,Task_ref* SelfTref)
{
	SelfTref->TimingWaiting.Blocking = Enable ;
	SelfTref->TimingWaiting.Ticks_Count = NoTICKS ;
	// Task Should be blocked
	SelfTref->TaskState = Suspend ;
	//to be suspended immediately
	MYRTOS_OS_SVC_Set(SVC_terminateTask);

}



void MYRTOS_STARTOS()
{
	OS_Control.OSmodeID = OsRunning ;
	//Set Default "Current Task =Idle Task"
	OS_Control.CurrentTask = &MYRTOS_idleTask ;
	//Activate IDLE Task
	MYRTOS_ActivateTask(&MYRTOS_idleTask);
	//Start Ticker
	Start_Ticker(); // 1ms

	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	//Switch Thread Mode SP from MSP to PSP
	OS_SWITCH_SP_to_PSP;
	OS_SWITCH_TO_Unprivilged;
	MYRTOS_idleTask.p_TaskEntry();
}

//The function iterates through the array of active tasks (OS_Control.OSTasks),
//		checks if the task state is Suspend (i.e. it's blocked), and if the task's timing wait
//				(OS_Control.OSTasks[i]->TimingWaiting) is enabled, decrements the wait ticks count.
//				If the count reaches 1, the task's blocking is disabled and its state is set to Waiting.
//				The function also invokes the MYRTOS_OS_SVC_Set function with the argument SVC_TaskWaitingTime.

void MYRTOS_Update_TasksWaitingTime()
{
	for (int i =0; i < OS_Control.NoOfActiveTasks ; i++  )
	{
		if (OS_Control.OSTasks[i]->TaskState == Suspend) //it is blocking until meet the time line
		{
			if (OS_Control.OSTasks[i]->TimingWaiting.Blocking == Enable)
			{
				OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count-- ;
				if (OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count == 1)
				{
					OS_Control.OSTasks[i]->TimingWaiting.Blocking = Disable ;
					OS_Control.OSTasks[i]->TaskState = Waiting ;
					MYRTOS_OS_SVC_Set(SVC_TaskWaitingTime);
				}
			}
		}
	}
}





MYRTOS_errorID MYRTOS_AcquireMutex(Mutex_ref* Mref , Task_ref* Tref)
{
	if(Mref->CurrentTUser == NULL) //not used
	{
		Mref->CurrentTUser = Tref ;
	}else
	{
		if(Mref->NextTUser == NULL)
		{
			Mref->NextTUser = Tref ;
			//move to Suspend state until be released
			Tref->TaskState = Suspend ;
			//to be suspended immediately
			MYRTOS_OS_SVC_Set(SVC_terminateTask);
		}else
		{
			return MutexisReacedToMaxNumberOfUsers ;
		}

	}
	return NoError ;
}
void MYRTOS_ReleaseMutex(Mutex_ref* Mref)
{
	if(Mref->CurrentTUser != NULL)
	{
		Mref->CurrentTUser = Mref->NextTUser  ;
		Mref->NextTUser  = NULL ;
		Mref->CurrentTUser->TaskState = Waiting ;
		MYRTOS_OS_SVC_Set(SVC_Activatetask);

	}

}
