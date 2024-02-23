/*
 * Week_2.c
 *
 * Created: 2-2-2024 16:44:35
 * Author : jeffw
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void opdrachtB1(void);
void opdrachtB2(void);
void opdrachtB3(void);
void opdrachtB4(void);
void opdrachtB5(void);

int main(void)
{
	DDRD = 0xF0;
	EICRA |= 0x0B;
	EIMSK |= 0x03;
	sei();
    
    while (1) 
    {
		PORTD ^= (1 << 7);
    }
}

/*Download ioisr.c uit de repository en executeer deze op het BIGAVR/UNI-DS board. Verklaar de werking*/
void opdrachtB1(void) {
	
}

/*Implementeer een looplicht applicatie waarbij de main() bestaat uit een initialisatie gedeelte met daarna een lege while(true) loop. 
In ISR_INT1 en ISR_INT2 maakt het looplicht steeds 1 stap. Het looplicht wordt dus gestuurd vanuit de ISR’s, niet vanuit de main().*/
void opdrachtB2(void) {
	
}


void opdrachtB3(void) {
	
}

void opdrachtB4(void) {
	
}

void opdrachtB5(void) {
	
}

ISR(INT0_vect) {
	PORTD |= (1 << 5);
}





