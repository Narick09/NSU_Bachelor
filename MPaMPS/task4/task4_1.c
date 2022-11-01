#include <avr/io.h>
#include <avr/interrupt.h>

#define XTAL 8000000L
#define baudrate 9600L
#define bauddivider (XTAL/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)
#define count_nums 4

char symbol = 'E';
const char term = '\n';
char send_count_flag = 0;
char count = 0;

//const int command_size = 4;
//char command[command_size];

ISR(USART_RXC_vect)
{
	symbol = UDR;//это же так работает?..
}

ISR(USART_UDRE_vect)
{
	send_count_flag = 1;
	if(count == count_nums){
		UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << TXCIE) | (0 << UDRIE);
		} else if (count == count_nums-1){
		UDR = term;
		count++;
		} else {
		count++;
		UDR = symbol;
	}
}

int main(void)
{
	DDRB = 0;
	PORTB |= 0x01;
	send_count_flag = 0;
	count = 0;
	
	UBRRL = LO(bauddivider);
	UBRRH = HI(bauddivider);
	
	UCSRA = 0;
	
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE)|(0<<UDRIE);
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	symbol = 'E';
	
	// 	for(int i =0; i < command_size - 1; i++){
	// 		command[i] = symbol;
	// 	}
	// 	command[command_size - 1] = term;
	
	sei();
	DDRB |= (1 << 3);
	PORTB |= (1 << 3);
	
	char button = 0x01;
	while(1)
	{
		button = PINB & 0x01;//вроде не должно быть перезаписи пина при этом?
		if(!button){
			if(send_count_flag){
				continue;
				} else {
				count = 0;
				UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE)|(1<<UDRIE);
			}
			} else {
			send_count_flag = 0;
		}
	}
}
