.equ pull_up_DDRD=0b00000000//scanning 1 in bits where 0 in port //to DDRD
.equ pull_up_PortD=0b11110000//vcc for buttons - scanning zero here //to PortD
.equ LED_out=0b11110000//mb make it in RAM //to portA
.equ LED_power=0b00000100//to portD
.equ unchanged_buttons=0b00110000
.equ max_scan_zero=0b00100000
.equ max_pull_up_always=0b00001000

.def button_reg_mask=r16
.def button_prev=r19
.def button_act=r20
.def LED_status=r21
.def tmp=r17
.def tmp2=r18
.def tmp3=r23
.def buttons_conf=r22

/*.macro eor_LED_Status
ldi tmp3, 0
SBIC tmp, 

.endm*/

.org 0
jmp init

.org 100

init:
//инициализация стека
	ldi r16,Low(RAMEND)
	out SPL,r16
	ldi r16,High(RAMEND)
	out SPH,r16

/*	ldi button_act, pull_up_DDRD
	out DDRD, button_act

	ldi button_act, pull_up_PortD
	out PortD, button_act *///активировали подтягивающие резисторы

	//LEDs
	ldi LED_status, LED_out
	out DDRA, LED_status//работаем с этим портом, чтобы изменять горение светодиодиков, в зависимости от надатых кнопок
	out PORTA, LED_status//LED on
	//power:
	ldi tmp2, LED_power
	out DDRB, tmp2
	out PORTB, tmp2
	
	//ldi button_prev, unchanged_buttons
	//in button_act, PIND
	andi button_act, unchanged_buttons

setInitConf://c button_act тут все норм? зачем его тут активировать, а не в ините
	ldi button_act, pull_up_DDRD
	out DDRD, button_act

	ldi button_act, pull_up_PortD
	out PortD, button_act //активировали подтягивающие резисторы

	mov button_act, LED_status
	andi button_act, unchanged_buttons

	ldi button_reg_mask, 0b10000000
	mov button_prev, button_act
	//ldi buttons_conf, pull_up_PortD
	ldi tmp3, 0b10000000

loop://for matrix 2x2 - цикличный скан нулем кнопок
	ldi buttons_conf, pull_up_PortD
	eor buttons_conf, button_reg_mask
	
	mov tmp, buttons_conf//for reverse
	ldi tmp2, pull_up_PortD 
	eor tmp, tmp2

	out DDRD, tmp
	out PortD, buttons_conf
	//это дает нам конфигурацию сканирующего нуля по кнопкам. Далее смотрим, нажаты ли кнопки.
	call isCliked//if clicked smt, change LED_status inside it
	
	mov button_prev, button_act
	andi button_prev, unchanged_buttons

	lsr button_reg_mask
	cpi button_reg_mask, max_scan_zero
	breq setInitConf//end of loop
	rjmp loop

isCliked:
	in button_act, PIND
	andi button_act, unchanged_buttons
	cp button_act, button_prev
	brne check_buttons_init_for
	ret

check_buttons_init_for://buttons not in scaning 0
	//mov button_prev, button_act
	ldi tmp, max_scan_zero//kostyl
	//lsr tmp3


check_buttons_for:
	//mov tmp2, button_act
	call call_check
	lsr tmp
	cpi tmp, max_pull_up_always//end of for
	brne check_buttons_for//not end
	ret//to loop

call_check:
	mov tmp2, button_act
	and tmp2, tmp//neccessary bit
	eor tmp2, tmp//reverse bit
	
	and tmp2, button_prev//prev & !act
	//eor button_prev, tmp
	SBIC PIND, 7//6/7?? - нужен предпоследний
	lsr tmp3//не робит(
	SBIC PIND, 7//6/7?? - нужен предпоследний
	lsr tmp3//не робит(
	
	cpi tmp2, 0
	brne set_LED
	lsr tmp3
	ret//to check_buttons_for

set_LED:
	eor LED_Status, tmp3
	out PORTA, LED_status
	ret//to call_check

/*Delay:
	ldi r22, 0xFF ;load constant !!! рег buttons_conf пересекается с этим
	ldi r23, 0x0F
	;ldi r24, 0xFF

Delay_loop:
	subi r22, 1 ;-1
	sbci r23, 0 ;carry flag
	;sbci r24, 0 
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret*/
