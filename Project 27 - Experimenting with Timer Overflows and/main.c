/*
 * Project 27 - Experimenting with Timer Overflows and Interrupts
 *
 * Created: 4/19/2023 5:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "common_macros.h"


/*------------------------------ ISR's ---------------------------------------*/

ISR(TIMER1_OVF_vect) {
	
	SET_BIT(PORTB,PB1); /* Turn on led */
	_delay_ms(50); 
	CLEAR_BIT(PORTB,PB1);  /* Turn OFF Led  */
	
	SET_BIT(TIFR1,TOV1);   /* Clear Intterupt Flag */
}
	

int main(void)
{
	DDRB |= (1<<PB0) | (1<<PB1);  /* Set PB0 and PB1 as Output */ 
	
	TCCR1A = 0x00;        /* Normal , OverFlow Mode   */
	
	TCCR1B = (1<<CS11);    /* clk/8 (from prescaler) */
	
	TIMSK1 = (1<<TOIE1);   /*  Overflow Interrupt Enable */
	
	sei();                 /* Enable Global Intterupt */
	
	
	while(1)
	{
		/* Toggle Bit every 100 ms */
		TOGGLE_BIT(PORTB,PB0);   
		_delay_ms(100);
	}
	
}
