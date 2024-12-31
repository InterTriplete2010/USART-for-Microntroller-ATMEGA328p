#ifndef F_CPU
#define F_CPU 16000000UL	//16 MHz; this is the system clock of ATMEGA328p 
#endif

#include <avr/io.h>
#include <avr/delay.h>

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

	//Now enable the receiver and the transmitter by setting RXEN0 and TXEN0 to 1 
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);// | (1<<RXCIE0) | (1<<TXCIE0);	
	
	//Now set frame format: 8 bit for the data + 1 stop bit to interface with arduino
	UCSR0C |= (0<<USBS0) | (1<<UCSZ00) | (1<<UCSZ01);

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
//------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------//


int main(void)
{
    
	
	uart_init(MYUBRR);
	
    while (1) 
    {


		USART_Transmit(0x22);
		
		_delay_ms(2000);
		
	}

}
