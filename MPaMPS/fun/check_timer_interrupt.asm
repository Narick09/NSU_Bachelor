.def flag=r20
.def tmp1=r21

.cseg
.org 0
jmp start
.org $006
jmp time_int_handler

.org 100
//time_int_handler:
	

start:
    ldi r16, Low(RAMEND);stack
	out SPL, r16
	ldi r16, High(RAMEND)
	out SPH, r16

	//LEDs power
	sbi DDRB, 3
	//sbi PORTB, 3
	ldi tmp1, (1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS00)|(1<<CS02);phase PWM, prescaler 1024
	out TCCR0, tmp1
	ldi tmp1, 0xFD
	out OCR0, tmp1
	
	ldi flag, 1
	
	sbi DDRD, 7
	cbi PORTD, 7

	sbi DDRD, 5
	cbi PORTD, 5
	
	sbi DDRD, 4
	cbi PORTD, 4

	sei
	
	//configure timer 2
	ldi tmp1, (1<<WGM21) | (1<<CS20) | (1<<CS22);CTC, prescaler 1024
	out TCCR2, tmp1

	ldi tmp1, 1 << OCIE2
	out TIMSK, tmp1
	ldi tmp1, 1 << OCF2
	out TIFR, tmp1

	ldi tmp1, 0xFD
	out OCR2, tmp1




main_loop:
	jmp main_loop

time_int_handler:
	cpi flag, 1
	brne set_one
	ldi flag, 0
	
	cbi PORTD, 7
	cbi PORTD, 5
	cbi PORTD, 4
	call Delay
	reti

set_one:
	ldi flag, 1
	sbi PORTD, 7
	sbi PORTD, 5
	sbi PORTD, 4
	call Delay
	reti


Delay:
	ldi r16, 0xFF ;load constant 
	ldi r17, 0xFF
	ldi r18, 0x0F
Delay_loop:
	subi r16,1 ;-1
	sbci r17,0 ;carry flag
	sbci r18,0 
	brne Delay_loop ;branch, if not equal (Z!=0)
ret
