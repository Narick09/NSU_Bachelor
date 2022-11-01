//версия, чтобы при нажатии на ЛЮБУЮ кнопку изменялось состояние светодиода

//portC, 5-4(scan), D 2-3 - buttons(check)
//portA 3-0 - leds
//portb 3 - led power
.equ init_but_load		=	0b00110000	//соответствие кнопкам scan
.equ but_mask_not_scan_0=	0b00001100

.equ start_inc_scan_0	=	0b00100000	//portC, 5-4(scan)
.equ end_inc_scan_0		=	0b00001000	//сканирующий ноль по старшим 2м битам(матрица кнопок 2*2)
/*.equ start_value_check_bit=	0b00000000
.equ end_value_check_bit=	0b00000000*/

.def tmp1			=	r17
.def incr			=	r18				//для цикла сканирующего нуля - начальное состояние 10000000, далее - сдвиг вправо до max_inc
.def incr_check_bit	=	r19
.def LED_conf		=	r22				//зажигаем те светодиоды, где установлена 1 в этом регистре
.def buttons		=	r20
.def check_bit		=	r16
.def flag			=	r21

.macro in_but
	in buttons, pinD
	andi buttons, but_mask_not_scan_0
.endm

.cseg
.org 0
jmp start

.org 100
start:
    ldi tmp1, Low(RAMEND);stack
	out SPL, tmp1
	ldi tmp1, High(RAMEND)
	out SPH, tmp1

	ldi flag, 0
	ldi tmp1, init_but_load

	//LEDs
	ldi LED_conf, 0x0F
	out DDRA, LED_conf
	ldi LED_conf, 0x0F
	out PORTA, LED_conf
	//LEDs power
	sbi DDRB, 3
	//sbi PORTB, 3
	ldi tmp1, (1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS00);phase PWM, prescaler 1
	out TCCR0, tmp1
	ldi tmp1, 0xFD
	out OCR0, tmp1
	
	//buttons
	call init_buttons_conf
	ldi tmp1, but_mask_not_scan_0
	out portd, tmp1
	ldi tmp1, 0
	out ddrd, tmp1

init_loop:
	ldi incr, start_inc_scan_0

loop:
	//load mask of buttons
	ldi tmp1, init_but_load
	eor tmp1, incr
	out portC, tmp1//сначала порт, а потом ддр, чтобы не было ситуации кз на мнгновение переключения
	out ddrC, incr
	//-------------
	//call Delay
	in_but

	cpi buttons, but_mask_not_scan_0
	brne clr_LED//if_some_but_pushed//если то, что нам нужно - меняем состояние светодиода

	ldi flag, 0 //если брне не сработал, значит все кнопки отжаты, а значит надо вернуть флаг, чтобы можно было менять состояние светодиода

	jmp set_LED//--------------

return_loop:
	//перед выходом восстановить пулапы везде
	//call init_buttons_conf
	//call Delay

	lsr incr
	cpi incr, end_inc_scan_0
	brne loop
	jmp init_loop


if_some_but_pushed:
	cpi flag, 1//если уже поменяли состояние, то возвращаемся обратно
	breq return_loop
	ldi flag, 1
	call change_LED
	jmp return_loop

//----------------------------
set_LED:
	ldi LED_conf, 0x0F
	out PORTA, LED_conf
	jmp return_loop

clr_LED:
	ldi LED_conf, 0x00
	out PORTA, LED_conf
	jmp return_loop
	//------------------------
//worked
change_LED:
	push tmp1
	ldi tmp1, 0b00001111
	eor LED_conf, tmp1
	out PORTA, LED_conf
	pop tmp1
	ret

init_buttons_conf:
	//push buttons
	//push tmp1
	ldi tmp1, init_but_load
	out PORTC, tmp1
	ldi tmp1, 0
	out DDRC, tmp1//везде подтягивающие резисторы
	//pop tmp1
	//pop buttons
	ret

Delay:
	ldi r23, 0xFF ;load constant 
	ldi r24, 0xFF
Delay_loop:
	subi r23,1 ;-1
	sbci r24,0
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret
