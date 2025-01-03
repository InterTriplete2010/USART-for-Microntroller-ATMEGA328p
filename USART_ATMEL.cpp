#ifndef F_CPU
#define F_CPU 16000000UL	//16 MHz; this is the system clock of ATMEGA328p 
#endif

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#ifndef BAUD
#define BAUD 9600
#endif

//#define UBRR0 
#ifndef MYUBRR
#define MYUBRR ((F_CPU/(BAUD*16UL))-1) //The value 16 has been used because we are operating in single speed;
#endif

//Define the USART
void uart_init(unsigned int ubrr) {
	
	//Set the baud rate. This is a 12 bit register (pag 252)
	UBRR0H = (unsigned char) (ubrr >> 8);	//It contains the 4 most significant bits
	UBRR0L = (unsigned char)ubrr;	//It contains the 8 least significant bits

	//Now enable the receiver and the transmitter by setting RXEN0 and TXEN0 to 1 and the interrupts
	UCSR0B |= (1 << RXCIE0) | (1 << TXCIE0) | (1 << RXEN0) | (1 << TXEN0);	
	
	//Now set frame format: 8 bit for the data + 1 stop bit to interface with arduino.
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);

}

//Function for the transmission of the data
void USART_Transmit (uint8_t data)
{
	
	//Check if the transmit buffer is empty and ready to receive new data. This happens when the UCSR01 and the UDRE0 are empty
	while(!(UCSR0A & (1<<UDRE0)))
	{	
		
	}
	
	//Put the data into the buffer and send it out;
	UDR0 = data;
	
}

//Function for the reception of the data
unsigned char USART_Receive ()
{
	
	DDRD |= (1<<PORTD0);
	
	//Wait for the data to be received
	while (!(UCSR0A & (1<<RXC0)))
	{
	
	
		
	}
	
	//return buff_receive[1];
	return UDR0;
	
}
//------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------//
//Interrupts
ISR(USART_TX_vect)
{
	
	UCSR0B &= ~(1 << TXCIE0);	//Disable the interrupt
	PORTD &= ~(1 << PORTD5);
	
}

ISR(USART_RX_vect)
{
	
	UCSR0B &= ~(1 << RXCIE0);	//Disable the interrupt
	PORTD |= (1 << PORTD5);
	
}

//LED will be turned on when there is a change in PD7
ISR(PCINT2_vect)
{
	
	PORTD |= (1 << PORTD6);
	
}

int main(void)
{
	
	DDRD |= (1<<DDD5) | (1<<DDD6) | (1<<DDD7);
	
	PORTD |= (1 << PORTD7);
	
	uart_init(MYUBRR);
	
	//Enable the interrupt for the change of pin in D6
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT23);
	
	sei();	//Enable interrupts
	int flag_data = 0;
    while (1) 
    {


		//USART_Transmit(0x22);
		unsigned char data_rec = USART_Receive();
		
		_delay_ms(500);
		
		USART_Transmit(data_rec);
		
		_delay_ms(500);
		
		if (flag_data == 4)
		{
		
			PORTD &= ~(1 << PORTD7);
			
		}
		
			flag_data++;
			
			//Set again the interrupt flags
			UCSR0B |= (1 << RXCIE0) | (1 << TXCIE0);
	
	}
	

}
