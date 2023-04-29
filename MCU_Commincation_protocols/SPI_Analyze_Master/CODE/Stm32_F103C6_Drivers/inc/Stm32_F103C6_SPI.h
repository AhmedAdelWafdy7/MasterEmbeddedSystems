/*
 * Stm32_F103C6_SPI.h
 *
 *  Created on: Apr 27, 2023
 *      Author: Ahmed Adel Wafdy
 */

#ifndef INC_STM32_F103C6_SPI_H_
#define INC_STM32_F103C6_SPI_H_

//-----------------------------
//INCLUDES
//-----------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_GPIO.h"



/* ================================================================ */
/* ============= User type definitions (structures) =============== */
/* ================================================================ */

struct IRQ_SRC{
	uint8_t TXE:1; //TXE: Transmit buffer empty
	uint8_t RXNE:1; // RXNE: Receive buffer not empty
	uint8_t ERRT:1; //ERROR
	uint8_t RESERVED:5;
};
typedef struct {
	uint16_t	Baud_Rate;//specifies Baud rate Prescaler value
	// this parameter must be based on @ref SPI_BaudRate_define

	uint16_t Communicatin_Mode;//These bits are used for SPI bidirectional State
	// this parameter must be based on @ref SPI_Communicatin_Mode_define

	uint16_t	SPI_Mode;//This bit enables the transmitter or This bit enables the receiver
	// this parameter must be based on @ref SPI_Mode_define

	uint16_t	Frame_Format;//This bit determines Data can be shifted out either MSB-first or LSB-first.
	// this parameter must be based on @ref SPI_Frame_Format_define

	uint16_t Data_Size;//This bit selects Each data frame is 8 or 16 bits long depending on the size of the data programmed using
	// this parameter must be based on @ref SPI_Data_Size_define

	uint16_t IRQ_Enable;// SPI interrupt which will generate
	// this parameter must be based on @ref SPI_IRQ_define

	uint16_t CLK_Polarity;// control the Clock Polarity
	// this parameter must be based on @ref SPI_CLK_Polarity_define

	uint16_t CLK_Phase;// control the Clock Phase
	// this parameter must be based on @ref SPI_CLK_Phase_define

	uint16_t Slave_S_management;// Hardware or software slave select management
	// this parameter must be based on @ref SPI_Slave_S_management_define

	void(*IRQ_HANDLER)(struct IRQ_SRC irq_src); // setting the C function which will be call when Interrupt occur
}SPI_CONFIG_t;

/* ================================================================ */
/* =============== Macros Configuration References ================ */
/* ================================================================ */

/*@ref SPI_Mode_define
 */
/*
 * ===> Bit 2 MSTR: Master selection
0: Slave configuration
1: Master configuration*/
#define  SPI_Mode_Master							(0x1U<<2)
#define  SPI_Mode_Slave								(0x00000000U)

/*@ref SPI_Communicatin_Mode_define
 */
/*
====>Bit 15 BIDIMODE: Bidirectional data mode enable
0: 2-line unidirectional data mode selected
1: 1-line bidirectional data mode selected

===>Bit 14 BIDIOE: Output enable in bidirectional mode
This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
0: Output disabled (receive-only mode)
1: Output enabled (transmit-only mode)

====>Bit 10 RXONLY: Receive only
This bit combined with the BIDImode bit selects the direction of transfer in 2-line
unidirectional mode. This bit is also useful in a multislave system in which this particular
slave is not accessed, the output from the accessed slave is not corrupted.
0: Full duplex (Transmit and receive)
1: Output disabled (Receive-only mode)*/
#define  SPI_Communicatin_Mode_RXONLY				(0x1U<<10)
#define  SPI_Communicatin_Mode_2Lines				(0x00000000U)
#define  SPI_Communicatin_Mode_1Line_Receive		(0x1U<<15)
#define  SPI_Communicatin_Mode_1Line_Transmit		(0x1U<<15 | 0x1U<<14)

/*@ref SPI_Frame_Format_define
 */
/*Bit 7 LSBFIRST: Frame format
0: MSB transmitted first
1: LSB transmitted firs*/
#define  SPI_Frame_Format_LSB								(0x1U<<7)
#define  SPI_Frame_Format_MSB								(0x00000000U)

/*@ref SPI_Data_Size_define
 */
/*Bit 11 DFF: Data frame format
0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception*/
#define  SPI_Data_Size_16BIT							(0x1U<<11)
#define  SPI_Data_Size_8BIT								(0x00000000U)

/*@ref SPI_CLK_Polarity_define
 */
/*Bit1 CPOL: Clock polarity
0: CK to 0 when idle
1: CK to 1 when idle*/
#define  SPI_CLK_Polarity_When1								(0x1U<<1)
#define  SPI_CLK_Polarity_When0								(0x00000000U)


/*@ref SPI_CLK_Phase_define
 */
/*Bit 0 CPHA: Clock phase
0: The first clock transition is the first data capture edge
1: The second clock transition is the first data capture edge*/
#define  SPI_CLK_Phase_Second_Edge							(0x1U<<0)
#define  SPI_CLK_Phase_First_Edge							(0x00000000U)


/*@ref SPI_Slave_S_management_define
 */
/*
====>Bit 2 SSOE: SS output enable
	0: SS output is disabled in master mode and the cell can work in multimaster configuration
	1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
	in a multimaster environment.

=====>Bit 9 SSM: Software slave management
	When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
	0: Software slave management disabled
	1: Software slave management enabled
=====>Bit 8 SSI: Internal slave select
	This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
	NSS pin and the IO value of the NSS pin is ignored.*/
#define  SPI_Slave_S_management_HW_Slave							(0x00000000U)
#define  SPI_Slave_S_management_HW_Master_SS_Enable					(0x1U<<2)
#define  SPI_Slave_S_management_HW_Master_SS_Disable					~(0x1U<<2)

#define  SPI_Slave_S_management_SW_Internal_RESET					(0x1U<<9)
#define  SPI_Slave_S_management_SW_Internal_SET						(0x1U<<9 | 0x1U<<8)

/*@ref SPI_BaudRate_define
 */
/*Baud rate control
000: fPCLK/2
001: fPCLK/4
010: fPCLK/8
011: fPCLK/16
100: fPCLK/32
101: fPCLK/64
110: fPCLK/128
111: fPCLK/256*/
#define  SPI_BaudRate_2											(0x00000000U)
#define  SPI_BaudRate_4											(0b001U<<3)
#define  SPI_BaudRate_8											(0b010U<<3)
#define  SPI_BaudRate_16										(0b011U<<3)
#define  SPI_BaudRate_32										(0b100U<<3)
#define  SPI_BaudRate_64										(0b101U<<3)
#define  SPI_BaudRate_128										(0b110U<<3)
#define  SPI_BaudRate_256										(0b111U<<3)

/*@ref SPI_IRQ_define
 */
/*
====>Bit 7 TXEIE: Tx buffer empty interrupt enable
	0: TXE interrupt masked
	1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
====>Bit 6 RXNEIE: RX buffer not empty interrupt enable
	0: RXNE interrupt masked
	1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is
	set.
===>Bit 5 ERRIE: Error interrupt enable
	This bit controls the generation of an interrupt when an error condition occurs (CRCERR,
	OVR, MODF in SPI mode and UDR, OVR in I2S mode).
	0: Error interrupt is masked
	1: Error interrupt is enabled*/
#define SPI_IRQ_NONE										(0x00000000U)
#define SPI_IRQ_TXEIE										(0x1U<<7)
#define SPI_IRQ_RXNEIE										(0x1U<<6)
#define SPI_IRQ_ERRIE										(0x1U<<5)


enum Polling_Mechanism
{
	SPI_disable,
	SPI_enable
};

/* ================================================================ */
/* =========== APIs Supported by "MCAL SPI DRIVER" ================ */
/* ================================================================ */


void MCAL_SPI_Init(SPI_t *SPIx, SPI_CONFIG_t *Config);
void MCAL_SPI_DeInit(SPI_t *SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_t *SPIx);

void MCAL_SPI_Transmit(SPI_t *SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);
void MCAL_SPI_Receive(SPI_t *SPIx, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_En);

void MCAL_SPI_Transmit_Receive(SPI_t *SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);

#endif /* INC_STM32_F103C6_SPI_H_ */
