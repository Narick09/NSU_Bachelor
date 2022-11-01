.equ pull_up_DDRD=0b00001000
.equ pull_up_portD=0b00000100//vcc
.equ output_portB=0b00001000
.def button_prev=r19
.def button_act=r20
.def LED_status=r21
.def tmp=r17
.def tmp2=r18

.org 0
jmp init

/*.org 0x002
jmp intr_handle*/

.org 100

init:
//инициализация стека
	ldi r16,Low(RAMEND)
	out SPL,r16
	ldi r16,High(RAMEND)
	out SPH,r16

	;ldi button_act, pull_up_DDRD
	;out DDRD, button_act
	cbi DDRD, 2
	sbi portd, 2
	;ldi button_act, pull_up_portD
	;out PORTD, button_act //активировали подтягивающий резистор
	sbi DDRD, 3
	cbi portd, 3

	//LED
/*	ldi LED_status, output_portB
	out DDRB, LED_status
	out PORTB, LED_status//LED on*/
	sbi DDRB, 3
	sbi PORTB,3 
	ldi button_prev, pull_up_portD

start:
	in button_act, PIND
	//mov tmp, button_act
	call Delay

	mov tmp2, button_act
	ldi tmp, pull_up_portD
	andi tmp2, pull_up_portD//надо ли явно через логическое и с маской, выделяющей 1 бит в баттон_акт?
	eor tmp2, tmp//change necessary bit
	mov tmp, button_prev

	mov button_prev, button_act
	
	and tmp, tmp2 //prev & !act == true <=> prev == 1 && act == 0
	ldi tmp2, pull_up_portD
	eor tmp, tmp2//xor
	//andi tmp, pull_up_portD//mask
	cpi tmp, pull_up_portD//equal if ((prev == 1 && act == 0)) -> else

	brne else
	rjmp start
/*	in button_act, PIND
	sbrs button_act, 2
	call else
	rjmp start*/

else:
	;sleep?
	ldi tmp, output_portB
	eor LED_status, tmp//xot bit
	out PORTB, LED_status
	rjmp start

/*	in r16, PINB
	clr r17
	ldi r17, (1<<3)
	eor r16, r17
	out PORTB, r16
	ret*/

/*LEDoff:
	clr LED_status
	ldi LED_status, 1 << 3
	out PORTB, LED_status
	ret*/
	
/*//set INTO
	ldi r16, 1<<ISC10
	out MCUCR, r16
	clr r16
	ldi r16, 1<<INT0
	out GICR,r16
	clr r16
	ldi r16, 1<<INTF0
	out GIFR, r16
	clr r16

//allow interupt
	sei
start:
	jmp start

intr_handle:
	in r18,pinb
	sbrc r18,3
	cbi portb,3
	sbrs r18,3
	sbi portb,3
	reti*/

Delay:
	ldi r22, 0xFF ;load constant 
	ldi r23, 0x0F
	;ldi r24, 0xFF

Delay_loop:
	subi r22, 1 ;-1
	sbci r23, 0 ;carry flag
	;sbci r24, 0 
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret
