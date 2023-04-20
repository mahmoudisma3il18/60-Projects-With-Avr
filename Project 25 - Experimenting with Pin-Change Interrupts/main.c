/*
 * Project 25 - Experimenting with Pin-Change Interrupts
 *
 * Created: 4/18/2023 9:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "common_macros.h"


/*------------------------------- ISR's ------------------------------------*/
ISR(PCINT0_vect) {
	
	SET_BIT(PORTB,PB0);    /* Turn on LED  */
	_delay_ms(1000);
	CLEAR_BIT(PORTB,PB0);  /* Turn Off Led */
	
	SET_BIT(PCIFR,PCIF0);   /* Clear Flag   */
}

ISR(PCINT1_vect) {
	
	SET_BIT(PORTB,PB0);    /* Turn on LED  */
	_delay_ms(2000);
	CLEAR_BIT(PORTB,PB0);  /* Turn Off Led */
	
	SET_BIT(PCIFR,PCIF0);   /* Clear Flag   */
	
}

ISR(PCINT2_vect) {
	
	SET_BIT(PORTB,PB0);    /* Turn on LED  */
	_delay_ms(3000);
	CLEAR_BIT(PORTB,PB0);  /* Turn Off Led */
	
	SET_BIT(PCIFR,PCIF0);   /* Clear Flag   */
}


int main(void)
{
	SET_BIT(DDRB,PB0);     /* Set pin as output */
	
	CLEAR_BIT(DDRB,PB1);   /* Set Pin as INPUT*/
	
	CLEAR_BIT(DDRC,PC0);   /* Set Pin as input */
	
	CLEAR_BIT(DDRD,PD7);   /* Set Pin as input  */
	
	PCICR = 0x07 ;         /* Pin Change Interrupt Enable 0 ,  Pin Change Interrupt Enable 1 , Pin Change Interrupt Enable 2 */
	
	SET_BIT(PCMSK0,PCINT1);   /* Enable PCINT1 PB1 Pin  */
	
	SET_BIT(PCMSK1,PCINT8);   /* Enable PCINT8 PC0 Pin  */
	
	SET_BIT(PCMSK2,PCINT23);  /* Enable PCINT23 PD7 Pin  */
	
	sei();                 /* Enable Global Intterupt */
	
	while(1){
		
		/* Toggle Bit Every 100 milli second */
		
		TOGGLE_BIT(PORTB,PB0);
		_delay_ms(100);
		
	}
	
}
