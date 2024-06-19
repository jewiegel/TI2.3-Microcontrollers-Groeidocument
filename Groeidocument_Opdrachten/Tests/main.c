/*
 * Tests.c
 *
 * Created: 2-4-2024 15:21:28
 * Author : jeffw
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

#define BIT(x)		(1 << (x))
#define UART0_BAUD	9600					// Baud rate USART0
#define MYUBRR		F_CPU/16/UART0_BAUD - 1	// My USART Baud Rate Register
#define MAX_LENGHT	126

char character;
char buffer[MAX_LENGHT];
int read_position = 0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
/*void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );						// library function (max 30 ms at 8MHz)
	}
}*/


void usart0_init( void )						// initialize USART0 - receive/transmit
{
	
}

int main(void)
{	DDRF = 0xFF;
	usart0_init();
	lcd_init();
	sei();
	
	while (1)
	{
		
	}
	
	return 0;
}

ISR (USART0_TX_vect)
{
	PORTF ^= BIT(0);
	
}

ISR(USART0_RX_vect) // byte receive completed
{
	
	buffer[read_position] = UDR0;
	read_position++;
	//PORTA ^= BIT(7);
	
	if (read_position >= MAX_LENGHT)
	{
		read_position = 0;
	}
	
	lcd_clear();
	display_text_lcd(buffer);
}

ISR(INT0_vect)
{
	
}

