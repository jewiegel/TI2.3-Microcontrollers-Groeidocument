/*
 * Eindopdracht.c
 *
 * Created: 2-4-2024 13:33:01
 * Author : jeffw
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "include/lcd.h"
#include <util/delay.h>

#define FREQUENCY(frequency_value) ((F_CPU / (2 / frequency_value)) - 1)

unsigned int unlocked = 0; // Dient als boolean
unsigned int msCount = 0;
unsigned int timerRunning = 0; // Dient als boolean
unsigned int freq = 1000;
unsigned int beep = 0;

void closeDoor();
void openDoor();
void start_timer();
void stop_timer();
void beepTwice();

ISR(INT0_vect)
{
	PORTA ^= 0b10000000;
	OCR1A = FREQUENCY(1000);
	openDoor();
}

ISR(TIMER1_COMPA_vect)
{
	if (beep)
	{
		PORTD ^= (1 << 7);
	}
}

ISR(TIMER2_COMP_vect)
{
	msCount++;
	
	if (msCount >= 5000)
	{
		PORTA ^= 0b01000000;
		//OCR1A = FREQUENCY(500);
		closeDoor();
		beepTwice();
		PORTD = 0b00000000;
		msCount = 0;
	}
}

void closeDoor()
{
	if (unlocked)
	{
		stop_timer();
		lcd_clear();
		lcd_set_cursor(0);
		display_text_lcd("Vergrendeld");
		beep = 0;
		unlocked = !unlocked;
	}
}

void openDoor()
{
	if (!unlocked)
	{
		lcd_clear();
		lcd_set_cursor(0);
		display_text_lcd("Ontgrendeld");
		start_timer();
		beep = 1;
		unlocked = !unlocked;
	}
}

void init_timer()
{
	OCR1A = FREQUENCY(freq);
	TIMSK |= (1 << 4);
	TCCR1A = 0b00000000;
	TCCR1B = 0b00001101;	// compare output disconnected, CTC, RUN
	
	OCR2 = 7811;			// Compare value of counter 2
	TIMSK |= (1 << 7);		// T2 compare match interrupt enable
	TCCR2 = 0b00111000;		// Initialize T2: timer, timer stopped, compare output disconnected,CTC,RUN
}

void start_timer()
{
	TCCR2 = 0b00111011; // Hier zet ik de prescaler op 64 zodat de timer start.
}

void beepTwice()
{
	beep = 0;
	
	for (int i = 0; i < 2; i++)
	{
		PORTD = 0b10000000;
		wait(200);
		PORTD = 0b00000000;
		wait(200);	
	}
}

void stop_timer()
{
	TCCR2 = 0b00111000; // Hier zet ik de prescaler bits op 0 zodat de timer stopt
}

int main() 
{
	DDRA = 0xFF;
	DDRD = 0b10000000;
	
	EICRA |= (1 << ISC01) | (1 << ISC00); // Ik stel hier PORTD.0 op voor de rising edge.
	EIMSK |= (1 << INT0);
	init_timer();
	sei();
	
	lcd_init();
	_delay_ms(50);
	lcd_clear();
	lcd_set_cursor(0);
	display_text_lcd("Vergrendeld");
	
	while(1)
	{
		_delay_ms(1);
	}
	
	return 0;
}






