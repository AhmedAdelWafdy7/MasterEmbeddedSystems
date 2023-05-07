/*
 * Atmega32_Driver.c
 *
 * Created: 4/22/2023 11:34:52 AM
 * Author : Ahmed Adel Wafdy
 */ 

#include "Timer0.h"
#define F_CPU 8000000UL

uint32_t Timer_Counter = 0;

void Timer_CompareMatch_Interrupt_Handler(void)
{

}

void TIMER_INTREEUPT_HANDLER(void){
	Timer_Counter++;
	if(Timer_Counter == 3921) 
	{
		TOGGLE_BIT(PORTB, 0);
		
		Timer_Counter = 0;
	}
}
int main(void)
{

	SET_BIT(DDRB,0);
	/* Set compare value */
	MCAL_TIMER0_SetCompareValue(100);
	
	/* Set timer configuration */
	TIMER0_Config_t TIMER0_Config;
	
	TIMER0_Config.Timer_Mode = TIMER0_MODE_CTC;
	TIMER0_Config.Clock_Source = TIMER0_CLOCK_SOURCE_INTERNAL_PRESCALER_8;
	TIMER0_Config.IRQ_Enable = TIMER0_IRQ_ENABLE_TOIE0;
	TIMER0_Config.P_IRQ_CallBack = TIMER_INTREEUPT_HANDLER;
	
	MCAL_TIMER0_Init(&TIMER0_Config);
    /* Replace with your application code */
    while (1) 
    {
    }
}

