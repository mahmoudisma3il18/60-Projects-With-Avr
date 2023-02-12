/* Author : Mahmoud Ismail */
/* Date   : 12/2/2023      */
/* Project 4 -  Experimenting with NOT */


#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	
	DDRB = 0xFF; // PortB is OUTPUT
	
	PORTB = 0x0F ;   // Half is high and Half is Low
	
	while(1)
	{
		
		PORTB = ~PORTB  ;  // LOGIC LOW
		_delay_ms(500) ;
		
	}
	
	return 0;
}	