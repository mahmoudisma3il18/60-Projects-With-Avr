/* Author : Mahmoud Ismail */
/* Date   : 22/2/2023      */
/* Project 11 - Custom Functions That Return Values */


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

uint8_t timesThree(uint8_t numberToBeTimes) {
	
	uint8_t result ;
	
	result = numberToBeTimes * 3 ;
	
	return result;
}


	


int main(void) {
	
	DDRB = 0x01; // Pin0 is Output , Pin4 is Input
	
	uint8_t numberOfBlinking = timesThree(3);
	
	while(1) 
	{
		blinkLed(numberOfBlinking); // Call function and blink led 5 times
		_delay_ms(5000);
	}

	return 0;
}