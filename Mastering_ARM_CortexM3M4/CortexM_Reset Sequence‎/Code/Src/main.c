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


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


uint32_t IRQ_flag = 0;

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
void IRQ_EXTI9_callback(void){
	IRQ_flag = 1;
	Switch_CPU_Access_level(privilged);

}
int main(void)
{
	//Enable port B clock
	RCC_GPIOB_CLK_EN();
	//Enable AFIO clock
	RCC_AFIO_CLK_EN();	lcd_init();
	EXTI_PIN_CONFIG_t EXTI_cfg;
	EXTI_cfg.EXTI_PIN = EXTI9PB9;
	EXTI_cfg.TRIGGER_CASE = EXTI_TRIGGER_RISING_EDGE;
	EXTI_cfg.IRQ_HANDLER = IRQ_EXTI9_callback;
	EXTI_cfg.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_Init(&EXTI_cfg);
	Switch_CPU_Access_level(unprivilged);
	IRQ_flag = 1;


	while(1){
		if(IRQ_flag){
			lcd_clear();
			IRQ_flag = 0;
		}
	}
}

