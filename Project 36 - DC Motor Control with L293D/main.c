/*
 * Project 36 - DC Motor Control with L293D.c
 *
 * Created: 9/4/2023 2:12:44 AM
 * Author : Mahmoud Ismail
 */ 

#define F_CPU      1000000

#include <avr/io.h>
#include <util/delay.h>


/* 
Initialize PWM 
*/
void PWM_init(void) {
	
	/* 
	1. Clear OC2A on compare match, set OC2A at BOTTOM,
	(non-inverting mode).
	2. Fast PWM Mode.
	*/
	TCCR2A |= (1<<COM2A1) | (1<<WGM00) | (1<<WGM01);
	
	/* Set reg to zero */
	TCNT2 = 0x00;
	
	/* Set OC2A/PB3 as Output */
	DDRB &= ~(1<<PB3);
	
	/*
	1. clkT2S/(no prescaling)
	*/
	TCCR2B |= (1<<CS20);
	
}

void motorInit(void) {
	
	/* Set Motor pins as output */
	DDRB |= (1<<PB1) | (1<<PB2);
}

void motorForward(uint8_t duty) {
	
	/* Set Motor Direction */
	PORTB |= (1<<PB1);
	PORTB &= ~(1<<PB2);
	
	/* Set Motor speed */
	OCR2A = duty;
}

void motorBackward(uint8_t duty) {
	
	/* Set Motor Direction */
	PORTB |= (1<<PB2);
	PORTB &= ~(1<<PB1);
	
	/* Set Motor speed */
	OCR2A = duty;
}

void motorOff(void) {
	
	/* Set Motor Direction */
	PORTB &= ~(1<<PB2);
	PORTB &= ~(1<<PB1);
	
	/* Turn OFF PWM */
	TCCR2B = 0x00;
}


int main(void)
{
    /* Replace with your application code */
	
	/* Init PWM */
	PWM_init();
	
	/* Init Motor */
	motorInit();
	
	_delay_ms(1000);
    while (1) 
    {
		motorForward(64);
		_delay_ms(2000);
		motorOff();
		_delay_ms(2000);
		motorForward(255);
		_delay_ms(2000);
		motorOff();
		_delay_ms(2000);
		motorBackward(64);
		_delay_ms(2000);
		motorOff();
		_delay_ms(2000);
		motorBackward(255);
		_delay_ms(2000);
		motorOff();
		_delay_ms(2000);
    }
}

