/* Author : Mahmoud Ismail */
/* Date   : 22/2/2023      */
/* Project 12 - Building a Single-Digit Numerical Counter */


/*------------------------------ Includes -------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"

uint8_t sevenSegmentDisplay[] = {  0b00111111 , // 0
                        0b00000110 , // 1
                        0b01011011 , // 2
                        0b01001111 , // 3
                        0b01100110 , // 4
                        0b01101101 , // 5
                        0b01111101 , // 6
						0b00000111 , // 7
						0b01111111 , // 8
						0b01101111   // 9 
						        };


int main (void) {
	 
	 DDRB  = 0xFF ; // Set PortB as Output
	 DDRD  = 0xFC ; // Set PD0 and PD1 as Input
	 PORTD = 0xFC ; // Turn off Internal Pull up resistor for PD0 and PD1
	 
	 uint8_t numberToBeDisplayed = 0 ;
	 
	 while(1)
	 {
		 
		 PORTB = sevenSegmentDisplay[numberToBeDisplayed];
		 _delay_ms(150);
		 
		 if (BIT_IS_SET(PIND,PD0))
		 {
			 _delay_ms(50); // Debouncing
			 
			 if(BIT_IS_SET(PIND,PD0))
				 numberToBeDisplayed = 0;
		 }
		 
		 else if (BIT_IS_SET(PIND,PD1))
		 {	 
			 _delay_ms(50); // Debouncing
			 
			 if(BIT_IS_SET(PIND,PD1)) {
				 
				 numberToBeDisplayed++;
				 
				 if ( numberToBeDisplayed > 9 )
					 numberToBeDisplayed = 0 ;
			 } 
		 }
      }
	  
	return 0;
}