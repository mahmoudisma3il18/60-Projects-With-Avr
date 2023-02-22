/* Author : Mahmoud Ismail */
/* Date   : 14/2/2023      */
/* Project 9: A Simple Custom Function */


/*------------------------- Includes ----------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"

/*-------------------------- Defines ------------------------*/

#define TIME_DELAY                250

/*-------------------- Functions ---------------------------*/

void blinkTwice(void) {
	
	PORTB = 0xFF; // Turn On leds
	_delay_ms(TIME_DELAY);
	PORTB = 0x00; // Turn Off leds
	_delay_ms(TIME_DELAY);
	PORTB = 0xFF; // Turn on Leds
	_delay_ms(TIME_DELAY);
	PORTB = 0x00; // Turn off leds
	_delay_ms(TIME_DELAY);
}
	


int main(void) {
	
	DDRB = 0x01; // Pin0 is Output , Pin4 is Input
	
	while(1) 
	{
		blinkTwice(); // Call function
		_delay_ms(5000);
	}

	return 0;
}