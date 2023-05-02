/*
 * stm32f103x6.h
 *
 *  Created on: Apr 19, 2023
 *      Author: Ahmed Adel Wafdy
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_



//-----------------------------
//Includes
//-----------------------------

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_Memory_BASE						0x08000000UL
#define System_Memory_BASE						0x1FFFF000UL
#define SRAM_BASE								0x20000000UL

#define Peripherals_BASE						0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE		0xE0000000UL

//NVIC register map
#define NVIC_BASE								0xE000E100UL

#define NVIC_ISER0								*(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1								*(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2								*(volatile uint32_t *)(NVIC_BASE + 0x08)
#define NVIC_ICER0								*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1								*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2								*(volatile uint32_t *)(NVIC_BASE + 0x88)


//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_BASE								(Peripherals_BASE + 0x00021000UL)

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
//USART
#define USART2_BASE								0x40004400UL
#define USART3_BASE								0x40004800UL
//SPI
#define SPI2_BASE								0x40003800UL
#define SPI3_BASE								0x40003C00UL

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//USART
#define USART1_BASE								0x40013800UL
#define SPI1_BASE								0x40013000UL

//SPI
#define SPI1_BASE								0x40013000UL


//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE								(Peripherals_BASE + 0x00010800UL)
#define GPIOB_BASE								(Peripherals_BASE + 0x00010C00UL)
//C,D Partial included in LQFP48 Package
#define GPIOC_BASE								(Peripherals_BASE + 0x00011000UL)
#define GPIOD_BASE								(Peripherals_BASE + 0x00011400UL)
//E not included in LQFP48 Package
#define GPIOE_BASE								(Peripherals_BASE + 0x00011800UL)
//--------

#define AFIO_BASE								(Peripherals_BASE + 0x00010000UL)
#define EXTI_BASE								(Peripherals_BASE + 0x00010400UL)


//------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED0;
	volatile uint32_t MAPR2;

}AFIO_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

}RCC_t;


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-* PERIPHERAL INSTANTS -*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//RCC
#define RCC						((RCC_t *)RCC_BASE)
//GPIO
#define GPIOA					((GPIO_t *)GPIOA_BASE)
#define GPIOB					((GPIO_t *)GPIOB_BASE)
#define GPIOC					((GPIO_t *)GPIOC_BASE)
#define GPIOD					((GPIO_t *)GPIOD_BASE)
#define GPIOE					((GPIO_t *)GPIOE_BASE)
//AFIO
#define AFIO					((AFIO_t *)AFIO_BASE)
//EXTI
#define EXTI					((EXTI_t *)EXTI_BASE)
//USART
#define USART1					((USART_t *)USART1_BASE)
#define USART2					((USART_t *)USART2_BASE)
#define USART3					((USART_t *)USART3_BASE)
//SPI
#define SPI1					((SPI_t *)SPI1_BASE)
#define SPI2					((SPI_t *)SPI2_BASE)
#define SPI3					((SPI_t *)SPI3_BASE)





//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-* CLOCK ENABLE MACROS  -*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define RCC_GPIOA_CLK_EN()		(RCC->APB2ENR |= 1 << 2)
#define RCC_GPIOB_CLK_EN()		(RCC->APB2ENR |= 1 << 3)
#define RCC_GPIOC_CLK_EN()		(RCC->APB2ENR |= 1 << 4)
#define RCC_GPIOD_CLK_EN()		(RCC->APB2ENR |= 1 << 5)
#define RCC_GPIOE_CLK_EN()		(RCC->APB2ENR |= 1 << 6)
//AFIO
#define RCC_AFIO_CLK_EN()		(RCC->APB2ENR |= 1 << 0)

//USART
#define RCC_USART1_CLK_EN()		(RCC->APB2ENR |= 1 << 14)
#define RCC_USART2_CLK_EN()		(RCC->APB1ENR |= 1 << 17)
#define RCC_USART3_CLK_EN()		(RCC->APB1ENR |= 1 << 18)

#define RCC_USART1_CLK_RESET()	(RCC->APB2RSTR |= 1 << 14)
#define RCC_USART2_CLK_RESET()	(RCC->APB1RSTR |= 1 << 17)
#define RCC_USART3_CLK_RESET()	(RCC->APB1RSTR |= 1 << 18)

//SPI

#define RCC_SPI1_CLK_EN()	(RCC->APB2ENR |= 1 << 12) //SPI1 enable is in bit 12
#define RCC_SPI2_CLK_EN()	(RCC->APB1ENR |= 1 << 14) //SPI1 enable is in bit 14


#define RCC_SPI1_CLK_DI()	(RCC->APB2ENR &= ~(1 << 12)) //SPI1 disable is in bit 12
#define RCC_SPI2_CLK_DI()	(RCC->APB1ENR &= ~(1 << 14)) //SPI2 disable is in bit 14

#define RCC_SPI3_CLK_EN()		(RCC->APB2ENR |= 1 << 15)


#define RCC_SPI1_CLK_RESET()	(RCC->APB2RSTR |= 1 << 12)
#define RCC_SPI2_CLK_RESET()	(RCC->APB1RSTR |= 1 << 14)
#define RCC_SPI3_CLK_RESET()	(RCC->APB1RSTR |= 1 << 15)

#define RCC_SPI1_RESET()	(RCC->APB2RSTR |= 1 << 12) //SPI1 reset is in bit 12
#define RCC_SPI2_RESET()	(RCC->APB1RSTR |= 1 << 14) //SPI2 reset is in bit 14
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-* IVT  -*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40

//USART
#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39

//SPI
#define SPI1_IRQ	35
#define SPI2_IRQ	36
#define SPI3_IRQ	51



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-* NVIC IRQ (en/dis)able MACROS -*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define	NVIC_IRQ6_EXTI0_ENABLE			(NVIC_ISER0 |= 1<<6)
#define	NVIC_IRQ7_EXTI1_ENABLE			(NVIC_ISER0 |= 1<<7)
#define	NVIC_IRQ8_EXTI2_ENABLE			(NVIC_ISER0 |= 1<<8)
#define	NVIC_IRQ9_EXTI3_ENABLE			(NVIC_ISER0 |= 1<<9)
#define	NVIC_IRQ10_EXTI4_ENABLE			(NVIC_ISER0 |= 1<<10)
#define	NVIC_IRQ23_EXTI9_5_ENABLE		(NVIC_ISER0 |= 1<<23)
#define	NVIC_IRQ40_EXTI10_15_ENABLE		(NVIC_ISER1 |= 1<<8)//40-32=8 position-bit


#define	NVIC_IRQ6_EXTI0_DISABLE			(NVIC_ICER0 |= 1<<6)
#define	NVIC_IRQ7_EXTI1_DISABLE			(NVIC_ICER0 |= 1<<7)
#define	NVIC_IRQ8_EXTI2_DISABLE			(NVIC_ICER0 |= 1<<8)
#define	NVIC_IRQ9_EXTI3_DISABLE			(NVIC_ICER0 |= 1<<9)
#define	NVIC_IRQ10_EXTI4_DISABLE		(NVIC_ICER0 |= 1<<10)
#define	NVIC_IRQ23_EXTI9_5_DISABLE		(NVIC_ICER0 |= 1<<23)
#define	NVIC_IRQ40_EXTI10_15_DISABLE	(NVIC_ICER1 |= 1<<8)//40-32=8 position-bit

//USART

#define	NVIC_IRQ37_USART1_ENABLE		(NVIC_ISER1 |= 1<<5)//37-32=5
#define	NVIC_IRQ38_USART2_ENABLE		(NVIC_ISER1 |= 1<<6)//38-32=6
#define	NVIC_IRQ39_USART3_ENABLE		(NVIC_ISER1 |= 1<<7)//39-32=7


#define NVIC_IRQ37_USART1_DI()			(NVIC_ICER1 |= 1<<(USART1_IRQ - 32))// USART1
#define NVIC_IRQ38_USART2_DI()			(NVIC_ICER1 |= 1<<(USART2_IRQ - 32))// USART2
#define NVIC_IRQ39_USART3_DI()			(NVIC_ICER1 |= 1<<(USART3_IRQ - 32))// USART3


//SPI


#define NVIC_IRQ35_SPI1_EN()			(NVIC_ISER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_EN()			(NVIC_ISER1 |= 1<<(SPI2_IRQ - 32))	// SPI2
#define	NVIC_IRQ51_SPI3_ENABLE		(NVIC_ISER1 |= 1<<(SPI3_IRQ -32))//39-32=7

#define NVIC_IRQ35_SPI1_DI()			(NVIC_ICER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_DI()			(NVIC_ICER1 |= 1<<(SPI2_IRQ - 32))	// SPI2
#define	NVIC_IRQ51_SPI3_DISABLE		(NVIC_ICER1 |= 1<<(SPI3_IRQ -32))//39-32=7

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-* GENERIC MACROS -*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32F103X6_H_ */