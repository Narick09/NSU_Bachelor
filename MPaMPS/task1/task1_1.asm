.CSEG ;пространство кода на флэше
.def maximum=r21
.def minimum=r20

start:
	ldi r16, Low(RAMEND) ; stack pointer
	out SPL, r16
	ldi r16, High(RAMEND)
	out SPH, r16

	ldi minimum, 0x01
	ldi maximum, 0xF6

	sbi DDRB,3 ;data direction register (Port B)	
	;configure timer0:
	ldi r16, (1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS02);phase PWM, prescaler 256

	out TCCR0, r16

	mov r19, minimum;копируем значение с регистра с минимумом
	out OCR0, r19

for_up:
	inc r19
	out OCR0, r19
	call Init_delay
	cp r19, maximum
	brne for_up
	rjmp for_down

for_down:
	dec r19
	out OCR0, r19
	call Init_delay
	cp r19, minimum
	brne for_down
	rjmp for_up

Init_delay:
	ldi r16, 0xFF ;load constant 
	ldi r17, 0x2F

Delay_loop:
	subi r16,1 ;-1
	sbci r17,0
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret
