/*
 * servo.h
 *
 *  Created on: Jun 22, 2023
 *      Author: user
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_


#include "STM32F103x6.h"
#include "GPIO.h"
#include "Timer.h"

#define UP   1
#define Down 2


void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);


void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);




#endif /* INC_SERVO_H_ */
