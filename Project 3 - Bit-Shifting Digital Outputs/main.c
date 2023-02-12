/* Author : Mahmoud Ismail */
/* Date   : 10/2/2022      */
/* Project 3: Bit-Shifting Digital Outputs */

/*------------------------------------Includes---------------------------------*/

#include <avr/io.h>
#include <util/delay.h>


/*------------------------------- Definitions ---------------------------------*/

#define TIME_DELAY                  250



int main(void)
{
	DDRB = 0xFF ;    // PortB is OUTPUT
	
	uint8_t i;
	
	while(1)
	{
		for(i = 0 ; i < 8 ; i++)
		{
			PORTB  = 0x01 << i;
			_delay_ms(TIME_DELAY);
		}			
		
	}
	
	return 0;
}