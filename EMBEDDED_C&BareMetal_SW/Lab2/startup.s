/*
Ahmed Adel Wafdy
*/

.section .vectors

.word	0x20001000			/* stack top address */
.word 	_reset				/* Reset */
.word	Vector_handler		/* NMI */ 
.word	Vector_handler		/* Hard Fault */ 
.word	Vector_handler		/* MM Fault */ 
.word	Vector_handler		/* Bus Fault */ 
.word	Vector_handler		/* usage Fault */ 
.word	Vector_handler		/* RESERVED */ 
.word	Vector_handler		/* RESERVED */ 
.word	Vector_handler		/* RESERVED */ 
.word	Vector_handler		/* RESERVED */ 
.word	Vector_handler		/* SV call */ 
.word	Vector_handler		/* Debug RESERVED */ 
.word	Vector_handler		/* RESERVED */ 
.word	Vector_handler		/* PendSV */ 
.word	Vector_handler		/* SysTick */ 
.word	Vector_handler		/* IRQ0 */ 
.word	Vector_handler		/* IRQ1 */ 
.word	Vector_handler		/* IRQ2 */ 
.word	Vector_handler 



.section .text
_reset:
	bl main
	b  .

.thumb_func
Vector_handler:
	b _reset