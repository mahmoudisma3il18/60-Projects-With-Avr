/* Author : Mahmoud Ismail */
/* Date   : 14/2/2023      */
/* Project 10: Custom Functions with Internal Variables */


/*------------------------- Includes ----------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"

/*-------------------------- Defines ------------------------*/

#define TIME_DELAY                250

/*-------------------- Functions ---------------------------*/

void blinkLed(uint8_t numberOfBlinkingTimes) {
	
	uint8_t i;
	for(i = 0 ; i < numberOfBlinkingTimes ; i++)
	{
		PORTB = 0xFF; // Turn On leds
		_delay_ms(TIME_DELAY);
		PORTB = 0x00; // Turn Off Leds
		_delay_ms(TIME_DELAY);
	}
}
	


int main(void) {
	
	DDRB = 0x01; // Pin0 is Output , Pin4 is Input
	
	while(1) 
	{
		blinkLed(5); // Call function and blink led 5 times
		_delay_ms(5000);
	}

	return 0;
}