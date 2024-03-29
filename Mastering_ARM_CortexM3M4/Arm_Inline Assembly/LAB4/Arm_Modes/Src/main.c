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


void IRQ_EXTI9_callback(void){
	IRQ_flag = 1;

}
int VAL1 = 0;
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
	IRQ_flag = 1;
	__asm("nop\n\t nop \n\t nop");
// mov R0,VAL1
	__asm("mov R0,%0"
		   :"=r"(VAL1) );
	__asm("nop\n\t nop \n\t nop");

	while(1){
		if(IRQ_flag){
			lcd_clear();
			IRQ_flag = 0;
		}
	}
}

