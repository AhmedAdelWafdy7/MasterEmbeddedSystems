/*
 * Switching_LEDS.c
 *
 * Created: 4/19/2023 2:46:43 AM
 * Author : user
 */ 



#include "MemoryMap.h"
#include "Utilities.h"
#include "util/delay.h"
#define F_CPU		8000000UL
uint8_t led;
uint8_t button;

int main(void)
{
	//PORTA pins ====> Output
	DDRA = 0b11111111;
	//PORTC===>pin0====>input
	CLEAR_BIT(DDRC,0);
	SET_BIT(PORTC,0);

	/* Replace with your application code */
	while (1)
	{
		if(READ_BIT(PINC,0)==0){
			while(READ_BIT(PINC,0)==0){
				for(led=0;led<=7;led++){
					SET_BIT(PORTA,led);
					_delay_ms(1000);
				}				
			}
		}
		else{
				for(led=7;led>=0;led--){
					CLEAR_BIT(PORTA,led);
				}	
		}
	}
}


