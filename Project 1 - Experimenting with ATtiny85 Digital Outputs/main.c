// Author  : Mahmoud Ismail
// Date    : 5/2/2023

// Project 1 Experimenting with ATtiny85 Digital Outputs

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	
	DDRB = 0x0F; // Declare PortB as OUTPUT
	
	while(1)
	{
		PORTB = 0x0F; // Logic High on PORTB
		_delay_ms(1000);
		PORTB = 0x00; // Logic Low on PORTB
		_delay_ms(1000); // Delay for 1 sec
	}
	return 0;
}