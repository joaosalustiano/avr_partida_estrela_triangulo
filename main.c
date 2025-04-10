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
	
	int estado = 0;
	int tempo = 0;
	
    while (1) 
    {
		if(estado == 0)
		{
			PORTB &= ~(1<<3);
			PORTB &= ~(1<<4);
			PORTB &= ~(1<<5);
			
			//Caso o botão S1 seja acionado, o sistema é iniciado
			if(!(PINB & (1<<2))) //S1
			{
				estado = 1;
			}
		}
		if(estado == 1)
		{
			tempo = 5000;
			//Ligar K1 e K2
			PORTB |= (1<<5);
			PORTB |= (1<<4);
			
			//Avançar para o estado em que a contagem de 5 segundos é feita
			estado = 2;
		}
		if(estado == 2)
		{
			//É somado -1 à variável tempo até que o valor dentro dela seja 0, assim, o programa avança ao próximo estado
			--tempo;
			_delay_ms(1);
			if(tempo == 0)
			{
				estado = 3;
			}
		}
		if(estado == 3)
		{
			//Desligar K2 e ligar K3
			PORTB &= ~(1<<4);//K2
			PORTB |= (1<<3);//K3
			estado = 4;
		}
		if(estado == 4)
		{
			if(!(PINB & (1<<1))) //S0
			{
				estado = 0;
			}
		}
		if ((!( PINB & (1<<1)))&& (estado ==2))
		{
			estado = 0;
		}
    }
}