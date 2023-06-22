/*
 * RCC.h
 *
 *  Created on: Jun 22, 2023
 *      Author: user
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_



//includes
#include "STM32F103x6.h"
#include "GPIO.h"

#define HSI_RC_CLK 8000000


uint32_t MCAL_RCC_Get_SYS_CLKFreq(void);
uint32_t MCAL_RCC_Get_HCLK_Freq(void);
uint32_t MCAL_RCC_Get_PCLK1_Freq(void);
uint32_t MCAL_RCC_Get_PCLK2_Freq(void);



#endif /* INC_RCC_H_ */
