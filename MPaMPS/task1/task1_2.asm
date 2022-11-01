.CSEG
.def LED_conf=r16
.def Led_numbers=r17

start:
	ldi r16, Low(RAMEND) ; stack pointer
	out SPL, r16
	ldi r16, High(RAMEND)
	out SPH, r16
	
	ldi r18, 0xFF
	out DDRA, r18
	out PORTA, r18
	ldi r18, 0x0F
	out DDRD, r18

	ldi LED_conf, 0b10110011;number 2
	out PORTA, LED_conf
	ldi LED_numbers, 0b00101011;some 4 bits = zero always 
	;PD0 lights here
	out PORTD, LED_numbers
