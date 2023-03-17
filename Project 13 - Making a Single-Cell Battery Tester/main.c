/* Author : Mahmoud Ismail */
/* Date   : 17/3/2023      */
/* Project 13 -  Making a Single-Cell Battery Tester */


/*------------------------------ Includes -------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


/*----------------------- Functions -------------------------------*/

void startADC(void) {
	
	ADMUX  |= (1 << MUX1) ; // VCC used as Voltage Reference , set ADC2 (PB4)
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN) ; // Set prescaler speed for 1 MHz , Enable Adc
	
}

int main (void) {
	
	DDRB |= (1<<PB0) | (1<<PB1) ; // Set PB1 and PB0 as output for LEDS
	
	startADC();
	
	while(1)
	{
		ADCSRA |= (1<<ADSC); // Start Conversation
		
		while(BIT_IS_SET(ADCSRA,ADSC)); // Loop until conversation is done
		
		
		if(ADC >= 287) // Batter volt >= 1.4
		{
			PORTB = (1<< PB0); // Battery is healthy and turn green led
		}
		else if (ADC < 287) // Batter volt < 1.4
		{
			PORTB = (1<<PB1); // Battery is unhealthy and turn red led
		}
		else
		{
			// Do nothing
		}
		
	}
	
	return 0;
}