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


int main(void)
{
    /* Replace with your application code stinky winky*/
    while (1) 
    {
    }
}


void voorbeeld(void) {
	DDRD = 0xFF;
	PORTD = 0b11111111;
	_delay_ms(500);
	PORTD = 0b00000000;
	_delay_ms(500);
}

/*Maak een nieuwe applicatie die beurtelings de LED op PORTD, pin 7 (PORTD.7) en de LED op PORTD,
pint 6 (PORTD.6) om de 500ms laat oplichten. Ontwikkel de applicatie in de simulator en programmeer daarna het board (gaat veel sneller!)*/
void opdrachtB2(void) {
	
}

/*Maak een applicatie die de led op PORTD.7 laat knipperen als drukknop PORTC.0 laag (0) is (ingedrukt) en stopt bij het loslaten van de drukknop.*/
void opdrachtB3(void) {
	
}

/*Implementeer een looplicht applicatie op de LED’s van PORTD. Tussen elke verandering van output zit 50ms (milliseconden). Hoe zou je dit kunnen meten? Om een eenvoudig
looplicht te maken kun je gebruik maken van de shift operatoren in C (de >> en de <<). Dit heb je ook al gedaan in periode TI-1.1 op het GUI board.*/
void opdrachtB4(void) {
	
}

/*Een looplicht kun je implementeren met een schuifoperatie.
Als het gewenste patroon niet zo eenvoudig is kun je e.a. met een grote if-then-else of switch-case constructie implementeren.
Dit levert, in het algemeen, slecht onderhoudbare en starre implementaties op.
Beter is om een lichtpatroon te sturen vanuit een datastructuur, bijvoorbeeld een C array.
Enig idee hoe dit moet? Zie ook het voorbeeld in de code repository.
Implementeer een lichteffect met behulp van deze techniek. Bijvoorbeeld: YouTube */
void opdrachtB5(void) {
	
}

/*Toestanden. Maak een applicatie die de led op PORTD.7 laat knipperen met een frequentie van circa 1Hz (1 keer per seconde). 
Als nu PORTC.0 kort wordt ingedrukt gaat (en blijft) de led sneller knipperen (bijvoorbeeld 4Hz). 
Bij nogmaals kort drukken gaat (en blijft) de led weer knipperen met een frequentie van 1Hz.*/
void opdrachtB6(void) {
	
}

/*Zie breitspees*/
void opdrachtB7a(void) {
	
}

/*Zie breitspees*/
void opdrachtB7b(void) {
	
}

