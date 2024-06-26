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

void wait( int ms ) 
{
	for (int i=0; i<ms; i++) 
	{
		_delay_ms(1);		// library function (max 30 ms at 8MHz)
	}	
}

void opdrachtB2(void);
void opdrachtB3(void);
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
		PORTD = 0b10000000;
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
			PORTD = 0b10000000;
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

/*Implementeer een looplicht applicatie op de LED�s van PORTD. Tussen elke verandering van output zit 50ms (milliseconden). Hoe zou je dit kunnen meten? Om een eenvoudig
looplicht te maken kun je gebruik maken van de shift operatoren in C (de >> en de <<). Dit heb je ook al gedaan in periode TI-1.1 op het GUI board.*/
void opdracht_b4(void) 
{
	DDRD = 0xFF;
	
	while(1) 
	{
		PORTD = 0b10000000;
		for (int i = 0; i <= 7; i++)
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
	int blink_frequency = 1; // 1 for 1Hz, 4 for 4Hz

	while (1) 
	{
		if (!(PINC & 0b00000001)) 
		{
			_delay_ms(50);
			if (!(PINC & 0b00000001)) 
			{
				// Toggle frequency state
				if (blink_frequency == 1) 
					blink_frequency = 4;
				
				else 
					blink_frequency = 1;
				
				
				while (!(PINC & 0b00000001)) 
					_delay_ms(50);
			}
		}

		// Toggle LED
		PORTD ^= 0b10000000;

		// Delay based on the current blink frequency
		if (blink_frequency == 1) 
			_delay_ms(500); // 500ms on, 500ms off for 1Hz
		
		else 	
			_delay_ms(125); // 125ms on, 125ms off for 4Hz
	}
}



typedef enum { D7, D6, D5 } ENUM_EVENTS;
typedef enum { START, STATE_1, STATE_2, STATE_3, END } ENUM_STATES;
/* Define fsm transition */
typedef struct 
{
	void (*finit)(void);
	void (*fbody)(void);
	void (*fexit)(void);
	ENUM_STATES nextState;
} STATE_TRANSITION_STRUCT;

void handleEvent(ENUM_EVENTS event)
{
	// Call EXIT function old state
	if( fsm[state][event].fexit != NULL) {
		fsm[state][event].fexit() ;
	}
	
	// Set new state, -1 means 
	state = fsm[state][event].nextState;

	// Call INIT function
	if( fsm[state][event].finit != NULL) {
		fsm[state][event].finit() ;
	}

	// Call BODY function
	if( fsm[state][event].fbody != NULL) {
		fsm[state][event].fbody() ;
	}
}

//
// State S1
//
void s1(void){
	printf("s1\n");
}

//
// State S2
//
void s2(void){
	printf("s2\n");
}

//
// State S3
//
void s3(void){	
	printf("s3\n");
}

//
// State Start
//
void start(void){
	printf("start\n");
}

//
// State Stop
//
void end(void){	
	printf("end\n");
}


STATE_TRANSITION_STRUCT fsm[5][3] = 
{
	{ {s1,   NULL,  NULL, START}, 	{NULL, s1, NULL, STATE_1},		{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START},	{NULL, NULL, NULL, STATE_1},	{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START}, 	{NULL, s1, NULL, STATE_1}, 		{NULL, s3, NULL, STATE_3} },
	{ {NULL, NULL,  NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} },
	{ {NULL, start, NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} }
};

// State holder
ENUM_STATES state = START;

void opdrachtB7a(void) 
{
	DDRD = 0b00001111;			// Pins PORTD<7:4> input, PORTD<3:0)
	// output
	
	// Test
	handleEvent(D6);
	handleEvent(D5);
	handleEvent(D5);

	// wait forever
	while (1)
	{
	}
}

void opdrachtB7b(void) 
{
	
}

