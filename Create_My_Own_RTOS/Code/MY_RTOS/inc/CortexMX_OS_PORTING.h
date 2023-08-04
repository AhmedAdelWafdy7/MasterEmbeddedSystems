/*
 * CortexMX_OS_PORTING.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Ahmed Adel Wafdy
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "ARMCM3.h"


extern int _estack;
extern int _eheap;
#define MainStackSize		3072;

#define OS_SET_PSP(add) 			__asm volatile("mov r0,%0 \n\t msr PSP,r0" :: "r" (add) )
#define OS_GET_PSP(add) 			__asm volatile("mrs r0,PSP \n\t mov %0,r0": "=r" (add) )
#define OS_SWITCH_SP_to_PSP			__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_to_MSP			__asm volatile("mrs r0,CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")

#define OS_SWITCH_TO_privilged			    __asm("NOP \n\t NOP \n\t NOP \n\t")\			//Clear Bit0  in control register
											__asm("mrs r3,CONTROL \n\t"\
													"lsr r3,r3,#0x01 \n\t"\
	    									"lsr r3,r3,#0x01 \n\t"\
	    									"msr CONTROL , r3");

#define OS_SWITCH_TO_Unprivilged			    __asm(" mrs r3, CONTROL  \n\t" \
		  	  	  	  	  	  	  	  	  	  	  	  	  	  " orr r3,r3,#0x1   \n\t" \
															  	  " msr CONTROL, r3 ");



void Trigger_OS_PENDSV();
void Start_Ticker();

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
