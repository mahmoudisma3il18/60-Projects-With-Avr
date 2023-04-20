/*
 * Project 31 - Demonstrating PWM with the ATtiny85
 *
 * Created: 4/20/2023 6:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"



int main(void)
{
	
	DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB4);  /* Set PB0 and PB1 , PB4 as Output */
	
	/* Set up OC0A and OC0B with FAST PWM , Non-Invering , No presacler */
	
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01);    /* Fast PWM Mode , Non- Inverting */
	
	TCCR0B = (1<<WGM02) | (1<<CS00);                                /*(No prescaling) */
	
	/* Set up OC1B with CTC Mode , No presacler */
	
	GTCCR = (1<<PWM1B) | (1<<COM1B0);    /*  Pulse Width Modulator B Enable,  Toggle the OC1B output line */
	
	uint8_t duty_cycle = 0;
	
	while(1)
	{
		for(duty_cycle = 0 ; duty_cycle < 255;duty_cycle++)
		{
			OCR0A = duty_cycle;
			OCR0B = duty_cycle;
			OCR1B = duty_cycle;
			_delay_ms(500);
		}
		
		for(duty_cycle = 255 ; duty_cycle > 1;duty_cycle--)
		{
			OCR0A = duty_cycle;
			OCR0B = duty_cycle;
			OCR1B = duty_cycle;
			_delay_ms(500);
		}
		
		
	}
	
}
