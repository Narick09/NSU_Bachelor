//Нерабочий код - неудачная попытка исправить ошибку нуля 

.def flag=r16
.def zero_er0=r21
.def zero_er1=r22

.equ pull_up_DDRD=0b00001000
.equ pull_up_portD=0b00000100//vcc
.def button_prev=r19
.def button_act=r20
.def tmp=r17
.def tmp2=r18

.MACRO outi
LDI 	tmp,@1 			
OUT 	@0,tmp 	
.ENDM

.cseg
.org 0
jmp init

.org 0x1C//ADC Conversion Complete Handler
jmp ADC_handler

.org 100
ADC_handler:
	push r15//в дальнейшем юзается CPI
	in r15, sreg
	push tmp
	
	in tmp, ADCH
	call handler_part
	
	pop tmp
	out sreg, r15
	pop r15
	reti

init:
	ldi tmp, LOW(RAMEND)
	out SPL, tmp
	ldi tmp, HIGH(RAMEND)
	out SPH, tmp

	call Delay
	//LED
	sbi DDRB, 3
	//another LED
	sbi DDRD, 7

	;button
	cbi DDRD, 2
	sbi portd, 2
	sbi DDRD, 3
	cbi portd, 3

	ldi flag, 2//to check zero_error
	ldi zero_er0, 0
	ldi zero_er1, 0

	sei

	outi TCCR0, (1 << CS00) | (1 << WGM00) | (1 << WGM01) | (1 << COM01) // WGM00 WGM01 == 11 => PWM
	
	outi TCCR2, (1 << CS20) | (1 << WGM20) | (1 << WGM21) | (1 << COM21) // WGM00 WGM01 == 11 => PWM

	outi ADMUX, (1 << REFS0) | (1 << ADLAR) | (1 << MUX3)//Изначально - с 0-го пина считываем АЦПшкой

	outi ADCSRA, (1 << ADEN) | (1 << ADSC) |/* (1 << ADATE) |*/ (1 << ADIE)//correct ADATE?

start:
	in button_act, PIND
	//mov tmp, button_act
	call Delay

	mov tmp2, button_act
	ldi tmp, pull_up_portD
	andi tmp2, pull_up_portD
	eor tmp2, tmp//change necessary bit
	mov tmp, button_prev

	mov button_prev, button_act
	
	and tmp, tmp2 //prev & !act == true <=> prev == 1 && act == 0
	ldi tmp2, pull_up_portD
	eor tmp, tmp2//xor
	cpi tmp, pull_up_portD//equal if ((prev == 1 && act == 0)) -> else

	brne else
	rjmp start

else:
	ldi tmp, 0x01
	eor flag, tmp
	rjmp start

Delay:
	ldi r22, 0xFF ;load constant 
	ldi r23, 0x0F

Delay_loop:
	subi r22, 1 ;-1
	sbci r23, 0 ;carry flag
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret

handler_part:
	cpi flag, 1
	breq one_flag
	cpi flag, 2
	breq zero_flag_er
	cpi flag, 3
	breq one_flag_er

zero_flag:
	sub tmp, zero_er0
	out OCR0, tmp

	outi ADMUX, (1 << REFS0)|(1 << ADLAR)|(1 << MUX0)//change port configure - Muxes bits - change 0 to 1 port
	ret

one_flag:
	sub tmp, zero_er1
	out OCR2, tmp
	outi ADMUX, (1 << REFS0)|(1 << ADLAR) //change port configure - Muxes bits - change 1 to 0 port
	ret

zero_flag_er://check adc 0-0
	outi ADMUX, (1 << REFS0)|(1 << ADLAR)|(1 << MUX0)|(1 << MUX4)//change port configure - Muxes bits - check adc 1-1
	ldi flag, 3
	mov zero_er0, tmp
	//devide by 10(16 here):
	lsr zero_er0//?
	lsr zero_er0
	lsr zero_er0
	lsr zero_er0
	outi ADCSRA, (1 << ADEN) | (1 << ADSC) |/* (1 << ADATE) |*/ (1 << ADIE)
	ret

one_flag_er://check adc 1-1
	outi ADMUX, (1 << REFS0)|(1 << ADLAR) //change port configure - Muxes bits - to zero flag
	ldi flag, 0
	mov zero_er1, tmp
	outi ADCSRA, (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE)
	ret
