.def flag=r16

.def tmp0=r17
.def tmp1=r18
.def tmp=r19

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
	
	call handler_part
	
	out sreg, r15
	pop r15
	reti

init:
	ldi tmp, LOW(RAMEND)
	out SPL, tmp
	ldi tmp, HIGH(RAMEND)
	out SPH, tmp 
	//LED
	sbi DDRB, 3 
	//another LED
	sbi DDRD, 7 

	ldi flag, 0 
	sei 
	
	outi TCCR0, (1 << CS00) | (1 << WGM00)|(1 << WGM01)|(1 << COM01) // WGM00 WGM01 == 11 => PWM

	outi TCCR2, (1 << CS20) | (1 << WGM20)|(1 << WGM21)|(1 << COM21) // WGM00 WGM01 == 11 => PWM

	outi ADMUX, (1 << REFS0) | (1 << ADLAR) //Изначально - с 0-го пина считываем АЦПшкой

	outi ADCSRA, (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)

start:
	rjmp start

handler_part:
	cpi flag, 0
	brne one_flag

zero_flag:
	outi ADMUX, (1 << REFS0)|(1 << ADLAR)|(1 << MUX0)//change port configure - Muxes bits - change 0 to 1 port
	in tmp0, ADCH
	out OCR0, tmp0
	ldi flag, 1
	ret

one_flag:
	outi ADMUX, (1 << REFS0)|(1 << ADLAR) //change port configure - Muxes bits - change 1 to 0 port
	in tmp1, ADCH
	out OCR2, tmp1
	ldi flag, 0
	ret
