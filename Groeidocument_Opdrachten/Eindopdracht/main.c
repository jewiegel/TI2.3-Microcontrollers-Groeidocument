/*
 * Eindopdracht.c
 *
 * Created: 2-4-2024 13:33:01
 * Author : jeffw
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "include/lcd.h"


void init_timers(void)
{
	/* Init timer 1 */
	/* Init timer 2 */
}

void init_spi(void)
{
	
}

int main(void)
{
	init_timers();
	lcd_init();
	
    while (1) 
    {
		
    }
}

