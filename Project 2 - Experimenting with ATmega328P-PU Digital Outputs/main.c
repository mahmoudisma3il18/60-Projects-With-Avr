/* Author : Mahmoud Ismail */
/* Date   : 10/2/2023      */
/* Project 2 - Experimenting with ATmega328P-PU Digital Outputs */


#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	
	DDRB = 0xFF; // PortB is OUTPUT
	
	while(1)
	{
		PORTB = 0xFF ;   //LOGIC HIGH
		_delay_ms(500);  // Delay for 0.5 sec
		PORTB = 0x00  ;  // LOGIC LOW
		_delay_ms(500) ;
		
	}
	
	return 0;
}	