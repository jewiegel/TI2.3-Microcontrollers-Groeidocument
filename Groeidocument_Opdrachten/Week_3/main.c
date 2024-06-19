/*
 * Week_3.c
 *
 * Created: 8-3-2024 16:42:06
 * Author : jeffw
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <string.h>

#define BIT(x)			(1 << (x))
#define TIMER_FREQUENCY(time_period_ms) (1000 / time_period_ms)

void opdracht_b1(void);
void init_timer2(void);
void init_timer_2_b2(void);
void opdracht_b2(void);

int main(void)
{
	opdracht_b1();
	return 0;
}

void init_timer2(void)
{
	TCCR2 = 0x07;		// Initialize T2: ext.counting, rising edge, run
}

/* Realiseer met AVR T/C-2 (counter mode) een ‘teller’ die het aantal keren ‘toets indrukken’ telt en weergeeft op het LCD */
void opdracht_b1(void)
{
	char buffer[20];
	DDRD &= BIT(7);
	
	lcd_init();
	wait(10);
	
	lcd_clear();
	lcd_set_cursor(1);
	
	init_timer2();
	
	int previous_number = TCNT2;
	
	while(1)
	{
		if (previous_number != TCNT2)
		{
			previous_number = TCNT2;
			sprintf(buffer, "%d", TCNT2);
			lcd_clear();
			lcd_set_cursor(1);
			display_text_lcd(buffer);
		}
		wait(10);
	}
}


volatile int counter = 0;
volatile int msCount = 0;
int intervals[2] = {25, 15};

ISR( TIMER2_COMP_vect ) 
{
	msCount++;					// Increment ms counter
	if (msCount == intervals[counter % 2]) 
	{
		counter++;
		PORTD ^= BIT(7);		// Toggle bit 0 van PORTC
		msCount = 0;			// Reset ms_count value
	}
}

void init_timer_2_b2(void)
{
	OCR2 = 7811;				// Compare value of counter 2
	TIMSK |= BIT(7);		// T2 compare match interrupt enable
	sei();					// turn_on intr all
	TCCR2 = 0b00111011;		// Initialize T2: timer, prescaler=1024, compare output disconnected,CTC,RUN
}

/* Realiseer met de AVR T/C-2 (timer mode) pulsen op PORTD.7 van 15ms (milliseconden) ‘hoog’ en daarna 25ms ‘laag’. 
Realiseer dit door gebruik te maken van interrupts en meet met een oscilloscoop op PORTD.7 om het gewenste gedrag te controleren. */
void opdracht_b2(void)
{
	DDRD = 0xFF;				// set PORTC for output (toggle PC0)
	init_timer_2_b2();

	while (1) 
	{
		// do something else
		wait(10);			// every 10 ms (busy waiting
	}
}


