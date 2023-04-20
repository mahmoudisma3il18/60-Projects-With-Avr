/*
 * Project 29 - Using CTC Timers for Repetitive Actions with Longer Delays
 *
 * Created: 4/19/2023 6:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "common_macros.h"


/*----------------------------- Defines ---------------------------------------*/

#define     COUNTER_TARGET           5

/*-------------------------------- Global Varaibles ---------------------------*/

volatile uint8_t counter;        /* Counter  */

/*------------------------------ ISR's ---------------------------------------*/

ISR(TIMER1_COMPA_vect) {
	
	counter++;
	
	if(counter == COUNTER_TARGET)
	{
		SET_BIT(PORTB,PB1); /* Turn on led */
	    _delay_ms(50); 
	    CLEAR_BIT(PORTB,PB1);  /* Turn OFF Led  */
		
		counter = 0;  /* Increment from start */
	}
	
	SET_BIT(TIFR1,OCF1A);      /* Clear Flag */
}
	

int main(void)
{
	
	DDRB |= (1<<PB0) | (1<<PB1);  /* Set PB0 and PB1 as Output */
	
	TCCR1A = 0x00;         /* CTC Mode */

    TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10);   /* CTC Mode , clk/64 (from prescaler) */	
	
	TIMSK1 = (1<<OCIE1A);                         /* Output Compare A Match Interrupt Enable */
	
	OCR1A = 15625;                                /* Set ISR for every 1 Second */
	
	sei();                 /* Enable Global Intterupt */
	
	
	while(1)
	{
		/* Toggle Bit every 100 ms */
		TOGGLE_BIT(PORTB,PB0);   
		_delay_ms(100);
	}
	
}
