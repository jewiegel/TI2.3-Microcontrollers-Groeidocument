/*
 * Groeidocument_Jeff_Lucas.c
 *
 * Created: 2-2-2024 16:41:14
 * Author : jeffw
 */

#ifndef F_CPU
#define F_CPU 16000000UL // Clock speed
#endif 

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

PATTERN_STRUCT patterns[] = {
		{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
		{0x00, 100},
		{0xAA,  50}, {0x55,  50},
		{0xAA,  50}, {0x55,  50},
		{0xAA,  50}, {0x55,  50},
		{0x00, 100},
		{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
		{0x00, 0x00}
	};
	
typedef enum {START, STATE_1, STATE_2, STATE_3, END} STATES;

typedef struct 
{
	
}
	


void wait( int ms ) 
{
	for (int i=0; i<ms; i++) 
	{
		_delay_ms(1);		// library function (max 30 ms at 8MHz)
	}	
}

void opdracht_b4(void);
void opdrachtB5(void);
void opdrachtB6(void);
void opdrachtB7a(void);
void opdrachtB7b(void);

int main(void)
{
	opdrachtB6();
	return 1;
}

/*Maak een nieuwe applicatie die beurtelings de LED op PORTD, pin 7 (PORTD.7) en de LED op PORTD,
pint 6 (PORTD.6) om de 500ms laat oplichten. Ontwikkel de applicatie in de simulator en programmeer daarna het board (gaat veel sneller!)*/
void opdrachtB2(void) 
{
	DDRD = 0xFF;
	
	/* Replace with your application code*/
	while (1)
	{
		PORTD = 0b01000000;
		_delay_ms(500);
		PORTD = 0x00;
		_delay_ms(500);
	}
}

/*Maak een applicatie die de led op PORTD.7 laat knipperen als drukknop PORTC.0 laag (0) is (ingedrukt) en stopt bij het loslaten van de drukknop.*/
void opdrachtB3(void) 
{
	DDRD = 0xFF;
	
	while(1) 
	{
		if(PINC & 0b00000001) 
		{
			PORTD = 0b01000000;
			_delay_ms(500);
			PORTD = 0x00;
			_delay_ms(500);
		}
		else 
		{
			PORTD = 0b00000000;
		}
	}
}

/*Implementeer een looplicht applicatie op de LED’s van PORTD. Tussen elke verandering van output zit 50ms (milliseconden). Hoe zou je dit kunnen meten? Om een eenvoudig
looplicht te maken kun je gebruik maken van de shift operatoren in C (de >> en de <<). Dit heb je ook al gedaan in periode TI-1.1 op het GUI board.*/
void opdracht_b4(void) 
{
	DDRD = 0xFF;
	
	while(1) 
	{
		PORTD = 0b10000000;
		for (int i = 1; i <= 7; i++)
		{
			PORTD = (0b10000000 >> i);
			_delay_ms(70);
		}
		_delay_ms(1000);
	}
}

//if ((0 != PINA & MASK) && 0 == (prev_pina & MASK)) {
	//
//}

/*Een looplicht kun je implementeren met een schuifoperatie.
Als het gewenste patroon niet zo eenvoudig is kun je e.a. met een grote if-then-else of switch-case constructie implementeren.
Dit levert, in het algemeen, slecht onderhoudbare en starre implementaties op.
Beter is om een lichtpatroon te sturen vanuit een datastructuur, bijvoorbeeld een C array.
Enig idee hoe dit moet? Zie ook het voorbeeld in de code repository.
Implementeer een lichteffect met behulp van deze techniek. Bijvoorbeeld: YouTube */
void opdrachtB5(void) 
{
	DDRD = 0xFF;
	int index = 0;
	while(1) 
	{
		while(patterns[index].delay != 0)
		{
			PORTD = patterns[index].data;
			wait(patterns[index].delay);
			index++;
		}
		index = 0;
	}
}

/*Toestanden. Maak een applicatie die de led op PORTD.7 laat knipperen met een frequentie van circa 1Hz (1 keer per seconde). 
Als nu PORTC.0 kort wordt ingedrukt gaat (en blijft) de led sneller knipperen (bijvoorbeeld 4Hz). 
Bij nogmaals kort drukken gaat (en blijft) de led weer knipperen met een frequentie van 1Hz.*/
void opdrachtB6(void) 
{
	DDRD = 0xFF;
	
	int mask = 0b10000000;
	int prev_pina = PINA;
	int i = 0;
	
	while(1) 
	{
		prev_pina = PINA;
		if ((0 != PINA & mask) && 0 == (prev_pina & mask))
		{
			i++;
			PORTD = (0b10000000 >> i);
		}
	}
	
}

/*Zie breitspees*/
void opdrachtB7a(void) 
{
	
}

/*Zie breitspees*/
void opdrachtB7b(void) 
{
	
}

