/*
 * Project 34 - DC Motor Control with PWM and MOSFET
 * Created: 26/6/2023 1:01:55 AM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


#define    WAIT     100

void PWM_init(void) {
	
	DDRD |= (1 << PD6); /* Set PD6 as output , OC0A (Timer/Counter0 output compare match A output) */
	
	TCCR0A = (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);           /* Set OC0A ,FAST PWM , Non Inverting Mode  */
	 
	TCCR0B = (1<<WGM02) | (1<<CS00);                /* No prescaler */
}

void PWM_setDutyCycle(uint8_t dc) {
	
	OCR0A = dc ;    /* Set Duty Cycle to Register */
	
}

int main(void)
{
	
	PWM_init();    /* Init PWM  */
	
	uint8_t i;     /* Counter to set duty cycle */
	
	while(1)
	{
		/* Increment duty cycle every loop */
		for(i = 0 ; i < 254 ; i++) {
			PWM_setDutyCycle(i);
			_delay_ms(WAIT);
		}
		
		for(i = 254 ; i >1 ; i--) {
			PWM_setDutyCycle(i);
			_delay_ms(WAIT);
		}
	}
}
