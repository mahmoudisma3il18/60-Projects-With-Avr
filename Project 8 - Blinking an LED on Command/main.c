/* Author : Mahmoud Ismail */
/* Date   : 12/2/2023      */
/* Project 8 Blinking an LED on Command */


/*------------------------- Includes ----------------------*/



#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


int main(void) {
	
	DDRB = 0x01; // Pin0 is Output , Pin4 is Input
	
	while(1) 
	{
		if(BIT_IS_SET(PINB,PB4))
		{
			_delay_ms(50); // Delay for Debouncing
			if(BIT_IS_SET(PINB,PB4))
			{
				PORTB = 0x01; // Turn On Led
			}
		}
		else
		{
			PORTB = 0x00;
		}
	}

	return 0;
}