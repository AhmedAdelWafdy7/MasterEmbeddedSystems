/*
 * keypad.h
 *
 *  Created on: Jun 22, 2023
 *      Author: user
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_



#include "STM32F103x6.h"
#include "GPIO.h"



void keypad_Init();
char keypad_Read(void);

#endif /* INC_KEYPAD_H_ */
