#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

int main(void) 
{
	//Entradas
	DDRB &= ~((1<<2)|(1<<1)); // PB2 = S1 e PB1 = S0
	PORTB |= ((1<<2)|(1<<1)); // Para ligar o pull-up
	
	//Saídas
	DDRB |= ((1<<3)|(1<<4)|(1<<5));
	
	//Escrevendo nas saídas
	PORTB &=  ~(1<<3); //K3 
	PORTB &= ~(1<<4); //K2
	PORTB &= ~(1<<5); //K1 
		
	
    while (1) 
    {
		if( !((PINB & (1<<2)) )
		{
			PORTB |= (1<<5); //K1
			PORTB |= (1<<4); 
			_delay_ms(5000);
		}
    }
}
