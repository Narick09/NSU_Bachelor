.def LED_conf=r16;for LEDs in segment 0-7
.def Seg_numbers=r17;for segments 0-3

.macro	num_conf
.if	@0 < 1 ;means 0
ldi LED_conf, 0b11101011
.elif @0 < 2 ;means 1
ldi LED_conf, 0b00101000
.elif @0 < 3 ;means 2
ldi LED_conf, 0b10110011
.elif @0 < 4 ;means 3
ldi LED_conf, 0b10111010
.elif @0 < 5 ;means 4
ldi LED_conf, 0b01111000
.elif @0 < 6 ;means 5
ldi LED_conf, 0b11011010
.elif @0 < 7 ;means 6
ldi LED_conf, 0b11011011
.elif @0 < 8 ;means 7
ldi LED_conf, 0b10101000
.elif @0 < 9 ;means 8
ldi LED_conf, 0b11111011
.else ;means 9 and more
ldi LED_conf, 0b11111010
.endif
out PORTA, LED_conf
.endm

.CSEG
start:
	ldi r21, Low(RAMEND) ; stack pointer
	out SPL, r21
	ldi r21, High(RAMEND)
	out SPH, r21

	ldi Seg_numbers, 0b01111000
	out DDRD, Seg_numbers
	
	ldi Seg_numbers, 0b01111000
	out PORTD, Seg_numbers
	;---------------------------------
	ldi LED_conf, 0xFF
	out DDRA, LED_conf
	
	;out PORTA, LED_conf

	num_conf 7;changes LED_conf

LEDsPlay:
	
	ldi Seg_numbers, 0b00100000
	out PORTD, Seg_numbers
	num_conf 2
	call Delay

	ldi Seg_numbers, 0b00010000
	out PORTD, Seg_numbers
	num_conf 0
	call Delay

	ldi Seg_numbers, 0b00001000
	out PORTD, Seg_numbers
	num_conf 2
	call Delay

	ldi Seg_numbers, 0b01000000
	out PORTD, Seg_numbers
	num_conf 1
	call Delay
 
	rjmp LEDsPlay

Delay:
	ldi r18, 0xFF
	ldi r19, 0x0F
;	ldi r20, 0xAF

Delay_loop:
	subi r18,1 ;-1
	sbci r19,0
;	sbci r20,0
	brne Delay_loop 
	ret
