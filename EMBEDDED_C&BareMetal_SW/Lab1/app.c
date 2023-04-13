#include "uart.h"

unsigned char string[100] = " Learn-in-depth: Ahmed Adel Wafdy ";
void main(){
	UART_send_string(&string);
}