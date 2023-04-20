/*
 * Project 22 - Experimenting with Rising Edge Interrupts
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

int main(void)
{
	SET_BIT(DDRB,PB0);     /* Set pin as output */
	
	CLEAR_BIT(DDRD,PD44);  /* Set INT0 pin as INPUT  */
	
	EICRA = 0x03;          /* The rising edge of INT1 generates an interrupt request */
	
	SET_BIT(EIMSK,INT0);   /* Enable INT0 */
	
	sei();                 /* Enable Global Intterupt */
	
	while(1);
	
}
