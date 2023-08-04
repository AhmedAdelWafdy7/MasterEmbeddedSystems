/*
 * CortexMX_OS_PORTING.c
 *
 *  Created on: Aug 2, 2023
 *      Author: Ahmed Adel Wafdy
 */

#include "CortexMX_OS_PORTING.h"

#define _attribute_(ATT)  __attribute__ ((ATT))
#define __WEAK__	weak
#define __NACKED__	naked

unsigned char SysTickLED ;

_attribute_(__WEAK__) void HardFault_Handler (void) { while(1); }

_attribute_(__WEAK__) void MemManage_Handler(void) { while(1); }

_attribute_(__WEAK__) void BusFault_Handler(void) { while(1); }

_attribute_(__WEAK__) void UsageFault_Handler(void) { while(1); }

  __attribute ((naked)) void SVC_Handler(){
		__asm ("tst lr, #4 \n\t"
				"ITE EQ \n\t" //To execute Thumb instructions conditionally, you can either use an IT instruction, or a conditional branch instruction.
				"mrseq r0,MSP \n\t "
				"mrsne r0,PSP \n\t"
				"B OS_SVC");

  }


 void HW_Init(){
	  // initilaize Clock tree  (RCC -> Systick ) 8HZ

	 //decreas PENDSV priority to be equal than or equal SYSTICk
	 __NVIC_SetPriority(PendSV_IRQn, 15);
 }

 void Trigger_OS_PENDSV(){
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
 }
 void Start_Ticker(){
	  // initilaize Clock tree  (RCC -> Systick ) 8HZ
	 // x count = 1ms So we need 8000 tick
	 SysTick_Config(8000);
 }

 void SysTick_Handler(){
	 SysTickLED ^= 1;
	 MYRTOS_Update_TasksWaitingTime();
	 // Determine Pcurrent and Pnext
	 Decide_whatNext();
	 // Switch context &restore
	 Trigger_OS_PENDSV();
 }
