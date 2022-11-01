//не робит ><
//portD 7-4 - buttons
//portA 7-4 - leds
//portb 2 - led power
.equ but_mask			=	0b11110000	//соответствие кнопкам

.equ start_inc_scan_0	=	0b10000000
.equ max_inc_scan_0		=	0b00100000	//сканирующий ноль по старшим 2м битам(матрица кнопок 2*2)
.equ scan_0_mask		=	0b11000000	

.equ start_inc_check	=	0b00100000	//для внутреннего цикла - чек биты кнопок
.equ max_inc_check		=	0b00001000
.equ check_but_mask		=	0b00110000	
//.equ rows_number		=	2			//количество рядов
.equ columns_number		=	2			//количество колонок

//кладем состояния кнопок на стек, когда изменяем их, чтобы просканировать состояние
.def but_act	=	r21				//нынешнее состояние кнопок
.def but_prev	=	r20				//предыдущее состояние кнопок(на предыдущем такте)
//.def tmp_prev	=	r16
//.def tmp_act	=	r18
.def column_count=	r16
.def tmp1		=	r17
.def inc_1		=	r18				//для цикла сканирующего нуля - начальное состояние 10000000, далее - сдвиг вправо до max_inc
.def inc_2		=	r19
.def LED_conf	=	r22				//зажигаем те светодиоды, где установлена 1 в этом регистре
.def flag		=	r23				//flag для изменения горения
.def reg_to_Shift=	r24				//записать в этот регистр значение из того, который нужно сдвинуть
.def shift_value=	r25				//записать сюда значение, на сколько надо сдвинуть регистр


//проблемы: 
//*нужна задержка, чтобы успел установиться уровень на кнопке
//*нужно переделать под таймер, чтобы светодиоды зажигались по шиму
//*в нуле почему-то какие-то колебания
//*отрубить светодиоы, чтобы не было падения напряжения на них

.macro in_but
	//mov but_prev, but_act//need??????
	in but_act, pinD
	andi but_act, but_mask
.endm

.macro set_prev_but
	mov  but_prev, but_act
	andi but_prev, check_but_mask
.endm

.cseg
.org 0
jmp start
.org $006
jmp time_int_handler

.org 100
start:
    ldi r16, Low(RAMEND);stack
	out SPL, r16
	ldi r16, High(RAMEND)
	out SPH, r16

	ldi flag, 0

	//LEDs
	ldi LED_conf, 0xF0
	out DDRA, LED_conf
	out PORTA, LED_conf
	//LEDs power
	sbi DDRB, 3
	//sbi PORTB, 3
	ldi tmp1, (1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS00);phase PWM, prescaler 1
	out TCCR0, tmp1
	ldi tmp1, 0xFD
	out OCR0, tmp1
	
	//buttons
	ldi but_act, but_mask
	out PORTD, but_act
	ldi tmp1, 0
	out DDRD, tmp1//везде подтягивающие резисторы
	
	sei
	//configure timer 2
	ldi tmp1, (1<<WGM21)|(1<<CS20) |(1<<CS22);CTC, prescaler 1024
	out TCCR2, tmp1
	ldi tmp1, 0xFD
	out OCR2, tmp1

	ldi tmp1, 1 << OCIE2
	out TIMSK, tmp1
	ldi tmp1, 1 << OCF2
	out TIFR, tmp1
	
	//call Delay//is needed?:
	in_but//needed?
	set_prev_but

main_loop:
	cpi flag, 1
	brne PC+3
	call change_LED
	ldi flag, 0

/*	cpi inc_2, 0x0E
	brne PC+3
	call change_LED
	ldi inc_2, 0*/

	jmp main_loop

time_int_handler://надо, чтобы по прерыванию сканировался нулем 1 ряд и запоминался результат в спец регистр, а уже в главном цикле чекать, изменилось 
//ли состояние на кнопках ТАК, чтобы менять состояние светодиода. Также в прерывании должно определяться, какой ряд сканировать следующим
//ЗЫ определение координаты по изменившимся конфигурациям докрутить позже

/*	inc inc_2
	call delay
	reti

delay:
	ldi r16, 0xFF ;load constant 
	ldi r17, 0xF0
	//ldi r18, 0x0F
Delay_loop:
	subi r16,1 ;-1
	sbci r17,0 ;carry flag
	//sbci r18,0 
	brne Delay_loop ;branch, if not equal (Z!=0)
	ret*/


	ldi inc_1, 0
	out ddrd, inc_1

	//correct?
	//push but_act
	ldi but_act, but_mask
	out portd, but_act
	//pop but_act
	//-----

	ldi inc_1, start_inc_scan_0

	ldi shift_value, 0

	in_but//считываем значения кнопок

scan_0_loop:
	eor but_act, inc_1
	out ddrd, inc_1//на выход 10000000 or 01000000
	out portd, but_act//01xx0000 or 10xx0000

	//delay???????????
	in_but//считываем в but_act
	eor but_act, inc_1//возвращаем зануленный бит

	push but_act

	andi but_act, check_but_mask
	call compare

	pop but_act

	//...
	ldi tmp1, columns_number
	add shift_value, tmp1


	//главная часть цикла
	lsr inc_1
	cpi inc_1, max_inc_scan_0
	breq end_intr
	jmp scan_0_loop

end_intr:
	reti

compare:
	cp but_act, but_prev
	brne is_But_changed
	ret

is_But_changed:
	ldi inc_2, start_inc_check

	push but_act
	and but_act, inc_2
	cpi but_act, 0
	brne PC+2
	call check_prev
	pop but_act

	lsr inc_1
	ret

check_prev:
	push but_prev
	and but_prev, inc_2
	cp but_prev, inc_2
	brne PC+2


	ldi flag, 1
	
	pop but_prev

//worked
change_LED:
	push tmp1
	ldi tmp1, 0b10000000
	eor LED_conf, tmp1
	out PORTA, LED_conf
	pop tmp1
	ret 
//need to check
/*shift:
	push tmp1
	ldi tmp1, 0
	call shift_loop
	pop tmp1
	ldi shift_value, 0
	ret

shift_loop:
	cp tmp1, shift_value
	brne shifting
	inc tmp1
	ret

shifting:
	lsr reg_to_Shift
	jmp shift_loop*/
