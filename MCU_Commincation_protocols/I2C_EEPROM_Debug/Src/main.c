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
#include "Stm32_F103C6_I2C.h"
#include "I2C_Slave_EEPROM.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


//#define MCU_Act_As_Master
#define MCU_Act_As_Slave

uint16_t data;

 void Clock_Init(void);
/* =========== Main Program ========== */
int main()
{

	Clock_Init();

	EEPROM_Init();

		/* Test Case 1*/

		uint8_t CH1_To_Write[7] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07};
		uint8_t CH2_To_Read[7] = {0};

		EEPROM_Write_Nbyte(0xAF, CH1_To_Write, 7);
		EEPROM_Read_Byte(0xAF, CH2_To_Read, 7);

		/*Test Case 2 */

		CH1_To_Write[0] = 0xA;
		CH1_To_Write[1] = 0xB;
		CH1_To_Write[2] = 0xC;
		CH1_To_Write[3] = 0xD;

		EEPROM_Write_Nbyte(0xFFF, CH1_To_Write, 4);
		EEPROM_Read_Byte(0xFFF, CH2_To_Read, 4);

	/* Loop For Ever */
	while(1){}
}

/* ======== clock Initialize definition ======= */
void Clock_Init(void)
{
	/* Enable clock GPIOA */
	RCC_GPIOA_CLK_EN();

	/* Enable clock GPIOB */
	RCC_GPIOB_CLK_EN();

	/* Enable Clock For AFIO */
	RCC_AFIO_CLK_EN();
}





