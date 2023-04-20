/*
 * Project 28 - Using a CTC Timer for Repetitive Actions
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

ISR(TIMER1_COMPA_vect) {
	
	SET_BIT(PORTB,PB1); /* Turn on led */
	_delay_ms(50); 
	CLEAR_BIT(PORTB,PB1);  /* Turn OFF Led  */
	
	SET_BIT(TIFR1,OCF1A);      /* Clear Flag */
}
	

int main(void)
{
	
	DDRB |= (1<<PB0) | (1<<PB1);  /* Set PB0 and PB1 as Output */
	
	TCCR1A = 0x00;         /* CTC Mode */

    TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);   /* CTC Mode , clk/1024 (from prescaler) */	
	
	TIMSK1 = (1<<OCIE1A);                         /* Output Compare A Match Interrupt Enable */
	
	OCR1A = 14649;                                /* Set ISR for every 15 Second */
	
	sei();                 /* Enable Global Intterupt */
	
	
	while(1)
	{
		/* Toggle Bit every 100 ms */
		TOGGLE_BIT(PORTB,PB0);   
		_delay_ms(100);
	}
	
}
