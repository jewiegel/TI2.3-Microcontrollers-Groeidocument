/*
 * Week_4.c
 *
 * Created: 8-3-2024 16:52:05
 * Author : jeffw
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "lcd.h"

#define BIT(x) (1 << x)

void opdracht_b1(void);
void opdracht_b2(void);
void opdracht_b3(void);
void opdracht_b4(void);

int main(void)
{
	opdracht_b4();
    return 0;
}

void init_adc()
{
	ADMUX = 0b11100011;			// AREF=2.56V, result left adjusted, channel3 at pin PF3
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no start, no free running, division by 64
}

/*Laat de 10 bits AD-waarde van kanaal 1 op de led’s van Poort A en B zien. Bij Vin=0V zijn alle led’s uit, bij Vin = Vref zijn alle leds aan!*/
void opdracht_b2(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	init_adc();
	while (1)
	{
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		wait(100);				// every 100 ms (busy waiting)
	}
}

/*Verander het programma (voor kanaal 3 en voor 8 bits) zodat het alleen een AD-conversie uitvoert als jij dat wilt, dus op aanvraag. 
Maak daarvoor in main() een eindeloze lus met een wachtfunctie en een start voor de ADC.*/
void opdracht_b3(void)
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	init_adc();					// initialize ADC

	while (1)
	{
		ADCSRA |= BIT(6);
		while (ADCSRA & BIT(6));
		PORTA = ADCH;
		wait(100);				// every 100 ms (busy waiting)
	}
}

void opdracht_b4(void)
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	init_adc();					// initialize ADC
	
	lcd_init();
	lcd_clear();
	lcd_set_cursor(1);
	display_text_lcd("borek");
	char str[20];
	while (1)
	{
		ADCSRA |= BIT(6);
		while (ADCSRA & BIT(6));
		PORTA = ADCH;
		char i = ADCH;
		sprintf(str, "%d", i);
		lcd_clear();
		display_text_lcd(str);
		wait(500);				// every 1000 ms (busy waiting)
	}
}





