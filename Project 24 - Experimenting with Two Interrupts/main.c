/*
 * Project 24 - Experimenting with Two Interrupts
 *
 * Created: 4/18/2023 5:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "common_macros.h"


/*------------------------------- ISR's ------------------------------------*/
ISR(INT0_vect) {
	
	SET_BIT(PORTB,PB0);    /* Turn on LED  */
	_delay_ms(1000);
	CLEAR_BIT(PORTB,PB0);  /* Turn Off Led */
	
	SET_BIT(EIFR,INTF0);   /* Clear Flag   */
}

ISR(INT1_vect) {
	
	SET_BIT(PORTB,PB0);    /* Turn on LED  */
	_delay_ms(2000);
	CLEAR_BIT(PORTB,PB0);  /* Turn Off Led */
	
	SET_BIT(EIFR,INTF1);   /* Clear Flag   */
	
}
	

int main(void)
{
	SET_BIT(DDRB,PB0);     /* Set pin as output */
	
	CLEAR_BIT(DDRD,PD4);  /* Set INT0 pin as INPUT  */
	
	CLEAR_BIT(DDRD,PD3);  /* Set INT0 pin as INPUT  */
	
	EICRA = 0x0B;          /* The rising edge of INT0 generates an interrupt request, The falling edge of INT1 generates an interrupt request */
	
	SET_BIT(EIMSK,INT0);   /* Enable INT0 */
	
	SET_BIT(EIMSK,INT1);   /* Enable INT1 */
	
	sei();                 /* Enable Global Intterupt */
	
	while(1){
		
		/* Toggle Bit Every 100 milli second */
		
		TOGGLE_BIT(PORTB,PB0);
		_delay_ms(100);
		
	}
	
}
