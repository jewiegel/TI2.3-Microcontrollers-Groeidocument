/*
 * lcd.h
 *
 * Created: 9-2-2024 12:33:51
 *  Author: jeffw
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void wait(int ms);
void lcd_clear();
void lcd_init();
void display_text_lcd(char* displayText);
void lcd_set_cursor(int position);


#endif /* LCD_H_ */