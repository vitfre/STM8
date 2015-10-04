;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.2 #8938 (Jan 23 2014) (Linux)
; This file was generated Sun Jan 26 19:56:14 2014
;--------------------------------------------------------
	.module leds
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ;reset
	int 0x0000 ;trap
	int 0x0000 ;int0
	int 0x0000 ;int1
	int 0x0000 ;int2
	int 0x0000 ;int3
	int 0x0000 ;int4
	int 0x0000 ;int5
	int 0x0000 ;int6
	int 0x0000 ;int7
	int 0x0000 ;int8
	int 0x0000 ;int9
	int 0x0000 ;int10
	int 0x0000 ;int11
	int 0x0000 ;int12
	int 0x0000 ;int13
	int 0x0000 ;int14
	int 0x0000 ;int15
	int 0x0000 ;int16
	int 0x0000 ;int17
	int 0x0000 ;int18
	int 0x0000 ;int19
	int 0x0000 ;int20
	int 0x0000 ;int21
	int 0x0000 ;int22
	int 0x0000 ;int23
	int 0x0000 ;int24
	int 0x0000 ;int25
	int 0x0000 ;int26
	int 0x0000 ;int27
	int 0x0000 ;int28
	int 0x0000 ;int29
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	leds.c: 4: static void delay(uint32_t t)
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
_delay:
	sub	sp, #8
;	leds.c: 6: while(t--);
	ld	a, (0x0b, sp)
	ld	(0x05, sp), a
	ldw	y, (0x0d, sp)
	ld	a, (0x0c, sp)
00101$:
	ld	(0x02, sp), a
	ldw	x, y
	push	a
	ld	a, (0x06, sp)
	ld	(0x02, sp), a
	pop	a
	subw	y, #0x0001
	sbc	a, #0x00
	push	a
	ld	a, (0x06, sp)
	sbc	a, #0x00
	ld	(0x06, sp), a
	pop	a
	tnzw	x
	jrne	00101$
	ldw	x, (0x01, sp)
	jrne	00101$
	addw	sp, #8
	ret
;	leds.c: 9: int main( void )
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	leds.c: 11: GPIOC->DDR |= GPIO_PIN_3 | GPIO_PIN_4;
	ldw	x, #0x500c
	ld	a, (x)
	or	a, #0x18
	ldw	x, #0x500c
	ld	(x), a
;	leds.c: 12: GPIOC->CR1 |= GPIO_PIN_3 | GPIO_PIN_4;
	ldw	x, #0x500d
	ld	a, (x)
	or	a, #0x18
	ldw	x, #0x500d
	ld	(x), a
;	leds.c: 13: GPIOC->ODR |= GPIO_PIN_3;
	ldw	x, #0x500a
	ld	a, (x)
	or	a, #0x08
	ldw	x, #0x500a
	ld	(x), a
;	leds.c: 15: while(1)            
00102$:
;	leds.c: 17: delay(20000);
	push	#0x20
	push	#0x4e
	clrw	x
	pushw	x
	call	_delay
	addw	sp, #4
;	leds.c: 18: GPIOC->ODR ^= GPIO_PIN_3 | GPIO_PIN_4;
	ldw	x, #0x500a
	ld	a, (x)
	xor	a, #0x18
	ldw	x, #0x500a
	ld	(x), a
	jra	00102$
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
