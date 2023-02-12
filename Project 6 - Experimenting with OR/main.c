/* Author : Mahmoud Ismail */
/* Date   : 12 / 2 / 2023  */
/* Project 6: Experimenting with OR */


/*--------------------------------   Includes ----------------------------------*/

#include <avr/io.h>
#include <util/delay.h>

/*------------------------------ Defines ----------------------------------------*/

#define TIME_DELAY        250


int main (void) {
	
	DDRB = 0xFF; // PortB as Output
	
	uint8_t i ;
	
	while(1)
	{
		for(i = 0 ; i < 256 ; i++)
		{
			PORTB = 0x0F | i ; // Show numbers from 0 to 255 on leds
			_delay_ms(TIME_DELAY);
		}
	}
	
	return 0;
	
}