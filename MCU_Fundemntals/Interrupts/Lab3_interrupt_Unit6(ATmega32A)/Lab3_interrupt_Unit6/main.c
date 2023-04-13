/*
 * main.c
 *
 * Created: 4/13/2023 3:37:52 AM
 *  Author: Ahmed Adel Wafdy
 */
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SET_BIT(ADDRESS,BIT)	ADDRESS |= (1<<BIT)
#define RESET_BIT(ADDRESS,BIT)	ADDRESS &= ~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT)	ADDRESS ^= (1<<BIT)
#define READ_BIT(ADDRESS,BIT)	((ADDRESS & (1<<BIT) ) >>BIT )

#define IO_BASE		0x20
#define IO_PORTD	*(volatile unsigned int *)(IO_BASE+0x12)
#define IO_DDRD		*(volatile unsigned int *)(IO_BASE+0x11)
#define IO_MCUCR	*(volatile unsigned int *)(IO_BASE+0x35)
#define IO_GICR		*(volatile unsigned int *)(IO_BASE+0x3B)
#define IO_MCUCSR	*(volatile unsigned int *)(IO_BASE+0x34)



#include <xc.h>

int main(void)
{
	// output pins
	SET_BIT(IO_DDRD,5);
	SET_BIT(IO_DDRD,6);
	SET_BIT(IO_DDRD,7);
	//set int0 logical
	SET_BIT(IO_MCUCR,0);
	RESET_BIT(IO_MCUCR,1);
	//set int1 Rising edge
	SET_BIT(IO_MCUCR,2);
	SET_BIT(IO_MCUCR,3);
	//set int2 falling edge
	SET_BIT(IO_MCUCSR,6);
	//enable all interrupts
	SET_BIT(IO_GICR,5);
	SET_BIT(IO_GICR,6);
	SET_BIT(IO_GICR,7);
	//enable glopal interrupt	
		sei();
    while(1)
    {
		RESET_BIT(IO_PORTD,5);
		RESET_BIT(IO_PORTD,6);
		RESET_BIT(IO_PORTD,7);
		
    }
}
ISR(INT0_vect){
	SET_BIT(IO_PORTD,5);
	_delay_ms(1000);
}
ISR(INT1_vect){
	SET_BIT(IO_PORTD,6);
	_delay_ms(1000);
}
ISR(INT2_vect){
	SET_BIT(IO_PORTD,7);
	_delay_ms(1000);
}