/* Author : Mahmoud Ismail */
/* Date   : 17/3/2023      */
/* Project 14: Experimenting with an ATmega328P-PU ADC*/


/*------------------------------ Includes -------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"

/*------------------------- Functions -------------------------------*/

void startADC(void) {
	
	ADMUX  |= (1<<REFS0)|(1<<MUX0) | (1<<MUX2) ; //Use AVcc pin with ADC, Enable ADC5 (PC5)
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) ; // Enable ADC , Set prescaler to 1Mhz
}

uint16_t readAdc(void) {
	
	uint16_t retValue;
	
	ADCSRA |= (1<<ADSC); // Start ADC conversation
	
	while (BIT_IS_SET(ADCSRA,ADSC)); // Loop until ADC finish conversation 
	
	retValue = ADC;
	
	return retValue;
}
	


int main (void) {
	
	DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3); // Set PB0,PB1,PB2,PB3 as outputs for Leds
	
	startADC();
	
	uint16_t ADCvalue;
	
	while(1)
	{
		ADCvalue = readAdc(); // Read ADC Value
		
		if(ADCvalue>=0 && ADCvalue <256)
			PORTB = (1<<PB0); // Turn on First Led
		
		else if (ADCvalue>=256 && ADCvalue<512)
			PORTB = (1<<PB1); // Turn on second Led
		
		else if (ADCvalue>=512 && ADCvalue<768)
			PORTB = (1<<PB2); // Turn on third Led
		
		else if(ADCvalue>=768 && ADCvalue<1023)
			PORTB = (1<<PB3); // Turn on fourth Led
		
		else
		{
			//Do nothing
		}
	}
	return 0;
}