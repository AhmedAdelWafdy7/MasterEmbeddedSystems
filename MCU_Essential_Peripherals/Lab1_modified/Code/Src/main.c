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
#include "Stm32_F103C6_GPIO.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void clock_init()
{
	//Enable port A clock
	RCC_GPIOA_CLK_EN();
	//Enable port B clock
	RCC_GPIOB_CLK_EN();
}
//PORTB pins 1,13 output---PORTA pin1,13 input
void GPIO_init(){
	GPIO_PIN_CONFIG_T pin_cfg ;
	//PORTA pins 1,13 ===> input mode ,floating input
	// PORTA pin 1 ===>00: input mode ===>01: Floating input (reset state)
	pin_cfg.GPIO_PIN_NUMBER =GPIO_PIN_1;
	pin_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA,& pin_cfg);
	// PORTA pin 13 ===>00: input mode ===>01: Floating input (reset state)
	pin_cfg.GPIO_PIN_NUMBER =GPIO_PIN_13;
	pin_cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA,& pin_cfg);
	//==========================
	//PORTB pins 1,13
	//PORTB pin1 ===>01: Output mode, max speed 10 MHz.===>00: General purpose output push-pull
	pin_cfg.GPIO_PIN_NUMBER =GPIO_PIN_1;
	pin_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOB,& pin_cfg);
	//PORTB pin13 ===>01: Output mode, max speed 10 MHz.===>00: General purpose output push-pull
	pin_cfg.GPIO_PIN_NUMBER =GPIO_PIN_13;
	pin_cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOB,& pin_cfg);
}
void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}

int main(void)
{
	clock_init();
	GPIO_init();
	while(1){
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==0){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==0);
		}
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13)==1){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		}
		wait_ms(1);
	}
}