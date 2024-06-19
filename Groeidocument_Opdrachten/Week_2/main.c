/*
 * Week_2.c
 *
 * Created: 2-2-2024 16:44:35
 * Author : jeffw
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

void opdrachtB1(void);
void opdrachtB2(void);
void opdrachtB3(void);
void display(int number);
void opdrachtB4(void);
void opdrachtB5(void);
void nextRunningLight(void);

int main(void)
{
	opdrachtB4();
	return 1;
}

/*Download ioisr.c uit de repository en executeer deze op het BIGAVR/UNI-DS board. Verklaar de werking*/
void opdrachtB1(void) 
{
	
}

/*Implementeer een looplicht applicatie waarbij de main() bestaat uit een initialisatie gedeelte met daarna een lege while(true) loop. 
In ISR_INT1 en ISR_INT2 maakt het looplicht steeds 1 stap. Het looplicht wordt dus gestuurd vanuit de ISR’s, niet vanuit de main().*/

volatile int counter = 0;

//ISR(INT1_vect)
//{
	//nextRunningLight();
//}
//
//ISR(INT2_vect)
//{
	//nextRunningLight();
//}

void nextRunningLight(void)
{
	counter++;
	
	if (counter >= 8)
	{
		counter = 0;
		PORTC = 0b10000000;
		return;
	}
	PORTC = (0b10000000 >> counter);
	_delay_ms(100);
}

void opdrachtB2(void) 
{
	DDRC = 0xFF;
	
	EICRA |= (1 << ISC11) | (1 << ISC10);
	EICRA |= (1 << ISC21) | (1 << ISC20);
	
	EIMSK |= (1 << INT1); 
	EIMSK |= (1 << INT2);
	
	sei();
	PORTC = 0b10000000;
	while (1) 
	{
		
	}
}

#define MAX_SIZE 15
volatile int segmentCounter = 0;
int patterns[MAX_SIZE] = {0b00111111, 0b00110000, 0b01011011, 0b01111001, 0b01110100, 
						0b01101101, 0b01101111, 0b00111000, 0b01111111, 0b01111101,
						0b01111110, 0b01100111, 0b00001111, 0b01110011, 0b01001111};

//ISR(INT0_vect)
//{
	//segmentCounter++;
	//
	//if (segmentCounter >= 20) { segmentCounter = 0; }
	//
	//display(segmentCounter);
	//_delay_ms(100);
//}
//
//ISR(INT1_vect)
//{
	//segmentCounter--;
	//display(segmentCounter);
	//_delay_ms(100);
//}

/* Implementeer een functie waarmee een 7 segment display kan worden aangestuurd. */
void opdrachtB3(void) 
{
	EICRA |= (1 << ISC01) | (1 << ISC00); // INT0 rising edge
	EICRA |= (1 << ISC11) | (1 << ISC10); // INT1 rising edge
	EIMSK |= (1 << INT0);
	EIMSK |= (1 << INT1);
	sei();
	
	DDRB = 0xFF;
	PORTB = 0xFF;
	display(0);
	
	while(1) 
	{
		_delay_ms(100);
	}
}

void display(int number) 
{	
	if (number >= MAX_SIZE || number < 0)
	{
		PORTB = patterns[MAX_SIZE - 1];
	}
	else PORTB = patterns[number];
}

typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

PATTERN_STRUCT segment_pattern[23] = 
{
	{0x80, 150}, {0x00, 150},
	{0x80, 150}, {0x00, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x00, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x00, 150},
	{0xFF, 0}
};


void opdrachtB4(void) 
{
	DDRB = 0xFF;
	int index = 0;
	while (1) 
	{
		while(segment_pattern[index].delay != 0) 
		{
			PORTB = segment_pattern[index].data;
			wait(segment_pattern[index].delay);
			index++;
		}
		index = 0;
	}
}

void opdrachtB5(void) 
{
	// Init I/O
	DDRC = 0xFF;
	PORTC = 0xFF;

	// Init LCD
	lcd_init();
	
	_delay_ms(10);
	
	lcd_clear();

	// Write sample string
	lcd_set_cursor(2);
	display_text_lcd("Borek");

	// Loop forever
	while (1) {
		PORTC ^= (1<<0);	// Toggle PORTC.7
		wait( 250 );
	}

}





