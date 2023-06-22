
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*
 *  main.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Ahmed Adel Wafdy
 * @linked in	   : https://www.linkedin.com/in/ahmed-wafdy-094567242/
 */

//-----------------------------
//INCLUDES
//-----------------------------
#include "STM32F103x6.h"
#include "Servo.h"
#include "UART.h"
#include "GPIO.h"
#include "lcd.h"
#include "keypad.h"

/*=================Global Variables===============*/
uint16_t RFID_CARD_Enter;
uint16_t RFID_CARD_EXIT;

uint8_t pass[3] ={0};

unsigned char Available_Slots='3';
uint8_t Search_Done = 0;



void RFID_CARD_Enter_CallBack(void);
void RFID_CARD_EXIT_CallBack(void);

void Welcome(void);
void LCD_Display_Empty_Slots(void);
void LEDs_Init(void);
void PIRs_Init(void);
void Register_IDs_From_Admin(void);



LCD_Pins_Config_t LCD1 = {GPIOB,GPIOB,GPIOB,GPIOB,GPIO_PIN_11,GPIO_PIN_10};
LCD_Pins_Config_t LCD2 = {GPIOA,GPIOA,GPIOA,GPIOA,GPIO_PIN_5,GPIO_PIN_6};

int main(void)
{
	RCC_GPIOA_CLOCK_EN();
	RCC_GPIOB_CLOCK_EN();
	RCC_AFIO_CLOCK_EN();
	keypad_Init();
	Timer2_init();
	Servo1_Entry_Gate_Init();
	Servo2_Exit_Gate_Init();
	//==========================UART1 INIT=============================
	/* PA9  TX
	 * PA10 RX
	 * PA11 CTC
	 * PA12 RTS
	 */
	USART_Config_t uartCFG;

	uartCFG.BaudRate = UART_BaudRate_115200;
	uartCFG.HwFlowCtl = UART_HwFlowCtl_NONE;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uartCFG.P_IRQ_CallBack = RFID_CARD_Enter_CallBack;
	uartCFG.Parity = UART_Parity_NONE;
	uartCFG.Payload_Length = UART_Payload_Length_8B;
	uartCFG.StopBits = UART_StopBits_1;
	uartCFG.USART_Mode = UART_Mode_TX_RX;
	MCAL_UART_Init(USART1, &uartCFG);
	MCAL_UART_GPIO_Set_Pins(USART1);


	//==========================UART2 INIT=============================
	/* PA2  ->TX
	 * PA3 ->RX
	 * PA0 ->CTS
	 * PA1 ->RTS
	 */
	USART_Config_t uart2CFG;

	uart2CFG.BaudRate = UART_BaudRate_115200;
	uart2CFG.HwFlowCtl = UART_HwFlowCtl_NONE;
	uart2CFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uart2CFG.P_IRQ_CallBack = RFID_CARD_EXIT_CallBack;
	uart2CFG.Parity = UART_Parity_NONE;
	uart2CFG.Payload_Length = UART_Payload_Length_8B;
	uart2CFG.StopBits = UART_StopBits_1;
	uart2CFG.USART_Mode = UART_Mode_TX_RX;
	MCAL_UART_Init(USART2, &uart2CFG);
	MCAL_UART_GPIO_Set_Pins(USART2);

	lcd_init(&LCD1);
	lcd_init(&LCD2);
	LEDs_Init();
	PIRs_Init();

	/*==========Enter IDs To Store In Array Pass==========*/
	 Register_IDs_From_Admin();

	Welcome();
	dms(200);
	LCD_Display_Empty_Slots();


	int i=0;
	while(1)
	{
		if(Available_Slots>'0')
		{
			lcd_set_position(&LCD2, 2, 0);
			lcd_send_string(&LCD2,"Enter ID in");
			lcd_set_position(&LCD2,3,0 );
			lcd_send_string(&LCD2,"Card Reader");
			while(RFID_CARD_Enter ==0 && RFID_CARD_EXIT==0); //Wait for Enter any id
		}
		else
		{
			lcd_clear(&LCD2);
			lcd_set_position(&LCD2, 0, 0);
			lcd_send_string(&LCD2,"Parking Is Full");
			lcd_set_position(&LCD2, 2, 0);
			lcd_send_string(&LCD2,"Entry Not Allowed");
		}

		for(i=0;i<3;i++)
		{
			if(RFID_CARD_Enter == pass[i] || RFID_CARD_EXIT == pass[i] )
			{
				Search_Done=1;
			}

		}
		/*=====================Enter gate=====================*/
		if(Search_Done == 1 && RFID_CARD_Enter !=0 && Available_Slots>'0')
		{
			lcd_clear(&LCD2);
			lcd_set_position(&LCD2, 2, 3);
			lcd_send_string(&LCD2,"Right ID");
			lcd_set_position(&LCD2, 3, 0);
			lcd_send_string(&LCD2,"Entry gate Opens");

			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
			Servo1_Entry_Gate(UP);
			Available_Slots--;

			RFID_CARD_Enter =0;
			Search_Done =0;

			dms(300);

			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==1)
			{
				dms(200);
			}


			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
			Servo1_Entry_Gate(Down);


			Welcome();
			dms(200);
			LCD_Display_Empty_Slots();

		}
		/*===================Exit gate====================*/
		if(Search_Done == 1 && RFID_CARD_EXIT !=0 && Available_Slots<'3')
		{
			lcd_clear(&LCD2);
			lcd_set_position(&LCD2, 2, 3);
			lcd_send_string(&LCD2,"Right ID!");
			lcd_set_position(&LCD2, 3, 0);
			lcd_send_string(&LCD2,"Exit Gate Opens");

			//Green led*/
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
			Servo2_Exit_Gate(UP);
			Available_Slots++;
			dms(300);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==1) //Read the PIR2 state
			{
				dms(200);
			}
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
			Servo2_Exit_Gate(Down);

			RFID_CARD_EXIT =0;
			Search_Done =0;

			Welcome();
			dms(200);
			LCD_Display_Empty_Slots();
		}

		/*==================Wrong Id====================*/
		if(Search_Done == 0 && (RFID_CARD_Enter >0 || RFID_CARD_EXIT>0) )
		{
			lcd_clear(&LCD2);
			lcd_set_position(&LCD2, 0, 0);
			lcd_send_string(&LCD2,"Wrong ID!");
			lcd_set_position(&LCD2, 2, 3);
			lcd_send_string(&LCD2,"Try Again");

			for(i=0;i<3;i++)
			{
				MCAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
				dms(150);
			}
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1); //to ensure Red Led off after toggle

			Welcome();
			dms(150);
			LCD_Display_Empty_Slots();
			RFID_CARD_EXIT =0;
			RFID_CARD_Enter =0;
		}


	}

	return 0;
}


/*Call Back For UART*/
void RFID_CARD_Enter_CallBack(void)
{
	MCAL_UART_ReceiveData(USART1, &RFID_CARD_Enter, USART_disable);
	MCAL_UART_SendData(USART1, &RFID_CARD_Enter, USART_enable);
}

void RFID_CARD_EXIT_CallBack(void)
{
	MCAL_UART_ReceiveData(USART2, &RFID_CARD_EXIT, USART_disable);
	MCAL_UART_SendData(USART2, &RFID_CARD_EXIT, USART_enable);
}



void Welcome(void)
{

	lcd_clear(&LCD2);
	lcd_set_position(&LCD2, 1, 1);
	lcd_send_string(&LCD2,"Welcome in");
	lcd_set_position(&LCD2,2,0 );
	lcd_send_string(&LCD2,"BENWAFDY Parking");
}

void LCD_Display_Empty_Slots(void)
{
	lcd_clear(&LCD2);
	lcd_set_position(&LCD2, 0, 0);
	lcd_send_string(&LCD2,"Empty Slots=");
	lcd_set_position(&LCD2, 0, 14);
	lcd_send_char(&LCD2,Available_Slots);
}

void LEDs_Init(void)
{
	//RED LED A0
	GPIO_PIN_CONFIG_T PinCinfg;
	PinCinfg.GPIO_PIN_NUMBER=GPIO_PIN_0;
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10MHz;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	//GREEN LED A11
	PinCinfg.GPIO_PIN_NUMBER=GPIO_PIN_11;
	PinCinfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCinfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10MHz;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);
}

void PIRs_Init(void)
{
	//PIR1 A7
	GPIO_PIN_CONFIG_T PinCinfg;
	PinCinfg.GPIO_PIN_NUMBER=GPIO_PIN_7;
	PinCinfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	//PIR2 A1
	PinCinfg.GPIO_PIN_NUMBER=GPIO_PIN_1;
	PinCinfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(GPIOA, &PinCinfg);

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);

}

void Register_IDs_From_Admin(void)
{
			lcd_send_command(&LCD1, display_on_cursor_off);
			lcd_set_position(&LCD1, 0, 0);
			lcd_send_string(&LCD1,"IDs of system");
			lcd_set_position(&LCD1, 2, 0);
			lcd_send_string(&LCD1,"First  ID:");
			while(keypad_Read()=='N');
			pass[0]=keypad_Read();
			while(keypad_Read()!='N');
			lcd_set_position(&LCD1,14,1 );
			lcd_send_char(&LCD1, pass[0]);
			lcd_send_command(&LCD1, display_on_cursor_off);

			lcd_set_position(&LCD1, 3, 0);
			lcd_send_string(&LCD1,"Second ID:");
			while(keypad_Read()=='N');
			pass[1]=keypad_Read();
			while(keypad_Read()!='N');
			lcd_set_position(&LCD1, 10,2);
			lcd_send_char(&LCD1, pass[1]);
			lcd_send_command(&LCD1, display_on_cursor_off);

			lcd_set_position(&LCD1, 4, 0);
			lcd_send_string(&LCD1,"Third  ID:");
			while(keypad_Read()=='N');
			pass[2]=keypad_Read();
			while(keypad_Read()!='N');
			lcd_set_position(&LCD1, 10,3 );
			lcd_send_char(&LCD1, pass[2]);
			lcd_send_command(&LCD1, display_on_cursor_off);


			lcd_clear(&LCD1);
			lcd_set_position(&LCD1, 0, 0);
			lcd_send_string(&LCD1,"IDs are Stored");
			lcd_send_command(&LCD1, display_on_cursor_off);

			lcd_set_position(&LCD1, 2, 4);
			lcd_send_char(&LCD1, pass[0]);
			lcd_set_position(&LCD1, 2, 8);
			lcd_send_char(&LCD1, pass[1]);
			lcd_set_position(&LCD1, 2, 12);
			lcd_send_char(&LCD1, pass[2]);
}
