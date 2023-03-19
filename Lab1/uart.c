#include "uart.h"

#define UART0DR 	*((volatile unsigned int*)((unsigned int*)0x101f1000))

void UART_send_string(unsigned char *tx_string)
{
	while(*tx_string != '\0')
	{
		/* transimit char */
		UART0DR = (unsigned int)(*tx_string);
		tx_string++; /* next char */
	}
}
