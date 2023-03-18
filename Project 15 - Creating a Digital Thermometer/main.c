/* Author : Mahmoud Ismail */
/* Date   : 18/3/2023      */
/* Project 14: Experimenting with an ATmega328P-PU ADC*/


/*------------------------------ Includes -------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


/*------------------------- Global Variables -------------------------*/

uint8_t sevenSegmentDisplayValues[] = {  0b00111111, // 0
                                         0b00110000, // 1
										 0b01011011, // 2
										 0b01111001, // 3
										 0b01110100, // 4
										 0b01101101, // 5
										 0b01101111, // 6
										 0b00111000, // 7
										 0b01111111, // 8
										 0b01111101, // 9
};
										 

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


void showValue (uint8_t value) {
	
	PORTB = sevenSegmentDisplayValues[value] ; // Show value on Seven Segment Display
	
}
	


int main (void) {
	
	DDRB = 0x7F; // Set From PB0 to PB6 as output for sevent segment display
	
	startADC();
	
	uint16_t ADCvalue;
	
	uint8_t temp,temp_in_tenth,temp_in_ones;
	
	while(1)
	{
		ADCvalue = readAdc(); // Read ADC Value
		
		temp = (uint8_t)(((uint32_t)ADCvalue*125*5.0)/(1024*1.25)) - 50; // Minus -50 because we are in room temp
		
		temp_in_tenth = temp / 10;
		temp_in_ones  = temp % 10;
		
		showValue(temp_in_tenth); // Show tenth first
		_delay_ms(500);
		showValue(temp_in_ones); // Then show ones
		_delay_ms(500);
		
		
	}
	return 0;
}