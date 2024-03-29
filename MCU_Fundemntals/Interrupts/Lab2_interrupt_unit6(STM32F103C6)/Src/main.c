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

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// Ahmed Adel Wafdy
typedef volatile unsigned int vuint32_t;
#include <stdint.h>

//GPIOA Config ====> input pin0 - output pin13
#define GPIOA_BASE		0x40010800
#define GPIOA_CRL		*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)
//External interrupt configuration register 1
#define AFIO_BASE		0x40010000
#define AFIO_EXTICR1		*(volatile uint32_t *)(GPIOA_BASE + 0x08)
//======================================
// External interrupt registers ====> interrupt mask registers - Rising Edge trigger
//-SW interrupt event register- pending register
#define EXTI_BASE		0x40010400
#define EXTI_IMR		*(volatile uint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR		*(volatile uint32_t *)(EXTI_BASE + 0x08)
#define EXTI_SWIER		*(volatile uint32_t *)(EXTI_BASE + 0x10)
#define EXTI_PR			*(volatile uint32_t *)(EXTI_BASE + 0x14)
#define NVIC_ISER0		*(volatile uint32_t *)(0xE000E100)
//======================================
//Reset and clock control
#define RCC_BASE		0x40021000
#define RCC_IOPAEN		(1<<2)
#define RCC_APB2ENR		*(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_CFGR		*(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_CR			*(volatile uint32_t *)(RCC_BASE + 0x00)


void clock_init()
{
	RCC_APB2ENR |= RCC_IOPAEN;
	RCC_APB2ENR |= (1<<0);
}
GPIOA_Pin13_Output_Init(){
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
}
GPIOA_pin0_Input_Init(){
	GPIOA_CRL |= (1<<2);
}
int main(void)
{
	clock_init();
	GPIOA_Pin13_Output_Init();
	GPIOA_pin0_Input_Init();
	//select PORTA for EXTI0
	AFIO_EXTICR1 =0x0;
	//Rising  Trigger enabled
	EXTI_RTSR |= (1<<0);
	//Enable mask EXTI0
	EXTI_IMR |= (1<<0);
	//Enable NVIC IRQ 6 (EXTI0)
	NVIC_ISER0 |= (1<<6);
	while(1);
}
void EXTI0_IRQHandler(void){
	// toggle led
	GPIOA_ODR ^= (1<<13);
	//clear pending request
	EXTI_PR |= (1<<0);
}
