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
#include "lcd.h"
#include "keypad.h"
#include "se7en_segment.h"


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
void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}

int main(void)
{
	clock_init();
	lcd_init();
	se7ment_init();
	unsigned char key_pressed;
	lcd_send_string("hey there..Wafdy");
	wait_ms(30);
	lcd_clear();
	unsigned char LCD_DISPLAY [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	unsigned char DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
	for (unsigned char i = 0; i < 11; i++) {
		lcd_send_char(LCD_DISPLAY[i]);
		MCAL_GPIO_WritePort(GPIOB, DISPLAY[i] << 9);
		wait_ms(100);
	}
	lcd_clear();
	keypad_init();
	lcd_send_string("Keypad is ready");
	wait_ms(30);
	lcd_clear();

	while(1){
		key_pressed = keypad_get_char();
		switch (key_pressed) {
		case 'A':
			break;
		case '?':
			lcd_clear();
			break;
		default:
			lcd_send_char(key_pressed);
			break;
		}
	}
}
