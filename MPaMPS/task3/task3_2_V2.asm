//portD 7-4 - buttons
//portA 7-4 - leds
//portb 2 - led power
.equ but_mask=0b11110000
.equ max_inc=0b00100000
.def but_act=r21
.def but_prev=r20
.def tmp=r18
.def tmp1=r16
.def tmp2=r17
.def increment=r19
.def LED_conf=r22
.def LED_mask=r23

.macro in_but
	in but_act, pinD
	andi but_act, but_mask
.endm

.macro but_port_conf//for scanning zero
	out portD, @0 
	mov tmp1, @0
	ldi tmp2, 0xF0
	eor tmp1, tmp2
	//andi tmp1, but_mask
	out DDRD, tmp1
	//call Delay//?????
.endm

.cseg
start:
    ldi r16, Low(RAMEND);stack
	out SPL, r16
	ldi r16, High(RAMEND)
	out SPH, r16


	//LEDs
	ldi LED_conf, 0xF0
	out DDRA, LED_conf
	out PORTA, LED_conf
	//LEDs power
	sbi DDRB, 2
	sbi PORTB, 2

	//buttons
	ldi but_act, but_mask
	out PORTD, but_act
	ldi tmp1, 0
	out DDRD, tmp1//везде подтягивающие резисторы
	
	//call Delay//is needed?:
	in_but//needed?
	mov but_prev, but_act

init_loop:
	ldi increment, 0b10000000

main_loop:
//	in_but
	ldi tmp, but_mask
	eor tmp, increment
	and but_act, tmp
	and but_prev, tmp
	
	but_port_conf but_act

	in_but
	and but_act, tmp
	cp but_act, but_prev
	breq inc_l 
	
	//if (bp | !ba) = 0xF0:
	mov tmp1, but_act
	ldi tmp, 0xF0
	eor tmp1, tmp
	or but_prev, tmp1//bp | !ba
	cpi but_prev, 0xF0
	brne inc_l
	
	mov tmp1, but_act
	lsr tmp1
	lsr tmp1
	andi tmp1, 0x20
	mov tmp, but_act
	lsr tmp
	andi tmp, 0x10
	or tmp, tmp1
	lsr tmp
	lsr tmp
	lsr tmp
	lsr tmp
	call shift
	eor LED_conf, LED_mask
	out portA, LED_conf
	jmp inc_l

inc_l:
	or but_act, increment
	mov but_prev, but_act
	ldi tmp2, 0xF0
	but_port_conf tmp2
	lsr increment//i++
	cpi increment, max_inc//out?
	brne main_loop//not out
	rjmp init_loop//yes, out

shift:
	ldi LED_mask, 0b10000000
	ldi tmp1, 0x00

shift_loop:
	cp tmp1, tmp
	brne shift_r
	ret
shift_r:
	lsr LED_mask
	inc tmp1
	rjmp shift_loop

Delay:
	ldi tmp1, 0x0F ;load constant 
	ldi tmp2, 0x01
Delay_loop:
	subi tmp1,1 ;-1
	sbci tmp2,0 ;carry flag
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret
