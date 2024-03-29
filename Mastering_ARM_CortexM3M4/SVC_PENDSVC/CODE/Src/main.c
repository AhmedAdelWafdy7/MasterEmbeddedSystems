/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stm32f103x6.h>
#include "gpio.h"
#include "exti.h"
#include "lcd.h"

#include "core_cm3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


void PendSV_Handler(void)
{

}

void OS_SVC(int *Stack_Frame){
	uint8_t SVC_number;
	uint32_t val1,val2;
	val1 = Stack_Frame[0];
	val2 = Stack_Frame[1];
	SVC_number = *((unsigned char *) (((unsigned char*)Stack_Frame[6]) -2));
	switch(SVC_number){
	case 1:		//OS	// Add
		Stack_Frame[0] = val1 + val2 ;
		break;
	case 2:		//OS	//Sub
		Stack_Frame[0] = val1 - val2 ;
		break;
	case 3:		//OS		// Mul
		Stack_Frame[0] = val1 * val2 ;
		break;
	case 4:	//OS PendSV
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;
	}

}

int OS_SVC_Set(int a,int b,int SVC_ID){
	int result;
	switch(SVC_ID){
	case 1:		//OS	// Add
		__asm("svc #0x00");
		break;
	case 2:		//OS	//Sub
		__asm("svc #0x01");
		break;
	case 3:		//OS		// Mul
		__asm("svc #0x02");
		break;
	}

	// r0 ===> return value
	__asm("mov %0,r0":"=r"(result));
	return result;
}


enum CPU_Access_level{
	privilged,
	unprivilged
};
void Switch_CPU_Access_level(enum CPU_Access_level access_level){
	switch(access_level){
	case privilged:
	    __asm("NOP \n\t NOP \n\t NOP \n\t");
	    __asm("mrs r3,CONTROL \n\t"
	    		"lsr r3,r3,#0x01 \n\t"
	    		"lsr r3,r3,#0x01 \n\t"
	    		"msr CONTROL , r3");
	    __asm("NOP \n\t NOP \n\t NOP \n\t");
		break;
	case unprivilged:
	    __asm("NOP \n\t NOP \n\t NOP \n\t");
	    __asm("mrs r3,CONTROL \n\t"
	    		"orr r3,r3,#0x01 \n\t"
	    		"msr CONTROL , r3");
	    __asm("NOP \n\t NOP \n\t NOP \n\t");
		break;
	}

}
__attribute ((naked)) void SVC_Handler(){
	//Switch_CPU_Access_level(privilged);
	__asm("tst lr,#4 \n\t"
		   "ITE EQ \n\t"
			"mrseq r0,MSP \n\t"
			"mrsne r0,PSP \n\t"
			"B OS_SVC");

}
uint32_t IRQ_flag;
void IRQ_EXTI9_callback(void){


}


int main(void)
{
/*	//Enable port B clock
	RCC_GPIOB_CLK_EN();
	//Enable AFIO clock
	RCC_AFIO_CLK_EN();	lcd_init();
	EXTI_PIN_CONFIG_t EXTI_cfg;
	EXTI_cfg.EXTI_PIN = EXTI9PB9;
	EXTI_cfg.TRIGGER_CASE = EXTI_TRIGGER_RISING_EDGE;
	EXTI_cfg.IRQ_HANDLER = IRQ_EXTI9_callback;
	EXTI_cfg.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_Init(&EXTI_cfg);

	Main_OS();
	IRQ_flag = 1;
*/
	IRQ_flag = OS_SVC_Set(3, 2, 1);
	IRQ_flag = OS_SVC_Set(3, 2, 2);
	IRQ_flag = OS_SVC_Set(3, 2, 3);
	IRQ_flag = OS_SVC_Set(3,3,4);

	while(1){
		if(IRQ_flag){
			lcd_clear();
			IRQ_flag = 0;
		}
	}
}

