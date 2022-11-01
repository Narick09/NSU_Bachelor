.def tmp1=r16
.def tmp2=r18
.def count=r17
.def send_count=r19//для кнопки - чтобы отправлять данные 1 раз при нажатии
//если попытаться записать в регистр УДР данные для передачи без разрешения передачи, контроллер, видимо, сохранит этот момент в энергонезависимой памяти и 
//восстановит при включении
//по ком порту при отжатии кнопки перезагрузки МК отправлялось "ОК". А также можно было писать в окно в Путти что-то(правда куда оно посылалось - хз)
//Попытался записать в УДР что-то без разрешения прерываний и отправки по уарт - после этого, сколько бы не перезагружал Мк, платку, не перепрошивал - реакции 0

/*.equ 	XTAL = 8000000 	
.equ 	baudrate = 9600 */ 
.equ 	bauddivider = 51//XTAL/(16*baudrate)-1
.cseg
.org 0
jmp uart_init

.org $016
jmp USART_RXC ; USART RX Complete Handler
/*.org $018
jmp USART_UDRE ; UDR Empty Handler*/
.org $01A
jmp USART_TXC ; USART TX Complete Handler


.org 100
USART_TXC:
	ldi send_count, 1// - устанавливаем факт отправки
	cpi count, 0x03
	breq just_reti
	cpi count, 0x02//если последний символ - брне не сработает и установится знак переноса строки
	brne out_int
	push tmp1
	ldi tmp1, '\n'
	OUT UDR, tmp1
	pop tmp1
	inc count
	reti

out_int:
	inc count
	OUT UDR, tmp1
	reti

just_reti:
; глушим прерывание по опустошению, выходим из обработчика
	push tmp1
	LDI 	tmp1, (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE)|(0<<UDRIE)
	OUT 	UCSRB, tmp1
	pop tmp1
	//ldi count, 0
	reti

USART_RXC:
	in tmp1, UDR
	reti
	

uart_init:
    ldi tmp1, Low(RAMEND);stack
	out SPL, tmp1
	ldi tmp1, High(RAMEND)
	out SPH, tmp1
	//button
	cbi ddrb, 0
	sbi portb, 0

	ldi send_count, 0

	ldi count, 0

	in tmp1, SREG
	andi tmp1, 0b01111111
	out SREG, tmp1
		
	LDI 	tmp1, low(bauddivider)
	OUT 	UBRRL,tmp1
	LDI 	tmp1, high(bauddivider)
	OUT 	UBRRH,tmp1

	LDI 	tmp1,0
	OUT 	UCSRA, tmp1

; Прерывания разрешены, прием-передача разрешен.
	LDI 	tmp1, (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE)|(0<<UDRIE)
	OUT 	UCSRB, tmp1
 
; Формат кадра - 8 бит, пишем в регистр UCSRC, за это отвечает бит селектор
	LDI 	tmp1, (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1)
	OUT 	UCSRC, tmp1
	
	ldi tmp1, 'H'

	sei

	sbi ddrd, 4
	sbi portd, 4



main_loop:
/*	nop
	nop
	nop
	nop
	nop*/
	in tmp2, pinb//считываем кнопку
	andi tmp2, 0x01//pinb 2
	cpi tmp2, 0//- значит, кнопка нажата
	breq if_send
	ldi send_count, 0//если не перешли на if_send, значит кнопка не нажата - зафиксируем
	rjmp main_loop

if_send:
	cpi send_count, 0// - значит, еще отправки не было, надо устроить
	brne main_loop
	ldi count, 0
	push tmp2
	LDI tmp2, (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE)|(1<<UDRIE)
	OUT UCSRB, tmp2
	pop tmp2
	jmp main_loop
