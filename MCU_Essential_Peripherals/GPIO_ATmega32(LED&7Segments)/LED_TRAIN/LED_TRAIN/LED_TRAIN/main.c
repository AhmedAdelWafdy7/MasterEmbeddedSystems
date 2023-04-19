/*
 * LED_TRAIN.c
 *
 * Created: 4/19/2023 2:00:59 AM
 * Author : Ahmed Adel Wafdy
 */ 


#include "MemoryMap.h"
#include "Utilities.h"
#include "util/delay.h"
#define F_CPU		8000000UL
int led;
int main(void)
{
	//PORTA pins ====> input
	DDRA = 0b11111111;

    /* Replace with your application code */
    while (1) 
    {
		for(led=0;led<=7;led++){
			SET_BIT(PORTA,led);
			_delay_ms(1000);
		}
		for(led=7;led>=0;led--){
			CLEAR_BIT(PORTA,led);
			_delay_ms(1000);
		}
    }
}

