/* Author : Mahmoud Ismail */
/* Date   : 12 / 2 / 2023  */
/* Project 5: Experimenting with AND */


/*--------------------------------   Includes ----------------------------------*/

#include <avr/io.h>
#include <util/delay.h>

/*------------------------------ Defines ----------------------------------------*/

#define TIME_DELAY        500


int main (void) {
	
	DDRB = 0xFF; // PortB as Output
	
	uint8_t i ;
	
	while(1)
	{
		for(i = 0 ; i < 256 ; i++)
		{
			PORTB = 0xFF & i ; // Show numbers from 0 to 255 on leds
			_delay_ms(TIME_DELAY);
		}
	}
	
	return 0;
	
}