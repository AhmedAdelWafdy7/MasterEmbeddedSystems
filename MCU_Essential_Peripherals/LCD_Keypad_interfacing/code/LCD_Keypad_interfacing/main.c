/*
 * LCD_Keypad_interfacing.c
 *
 * Created: 4/22/2023 8:15:18 AM
 * Author : Ahmed Adel Wafdy
 */ 

#include <avr/io.h>
#include "LCD_driver/lcd.h"
#include "Keypad_driver/Kaypad.h"

int main(void)
{
	char char_pressed;
	lcd_init();
	keypad_init();
	_delay_ms(50);
	while(1){
		char_pressed = keypad_get_char();
		switch(char_pressed){
			case 'A':
				break;
			case '?':
				lcd_clear();
				break;
			default:
			lcd_send_char(char_pressed);		
		}
	}
}