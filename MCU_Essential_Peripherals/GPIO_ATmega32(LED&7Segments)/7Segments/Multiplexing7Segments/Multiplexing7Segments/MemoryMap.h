/*
 * MemoryMap.h
 *
 * Created: 4/19/2023 4:27:49 AM
 *  Author: user
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_


#define DDRA	*((volatile unsigned char*)0x3A)
#define PORTA	*((volatile unsigned char*)0x3B)

#define DDRC	*((volatile unsigned char*)0x34)
#define PORTC	*((volatile unsigned char*)0x35)
#define PINC	*((volatile unsigned char*)0x33)




#endif /* MEMORYMAP_H_ */