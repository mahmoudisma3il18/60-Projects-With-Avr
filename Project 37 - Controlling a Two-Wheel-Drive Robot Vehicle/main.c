/*
 * Project 37 - Controlling a Two-Wheel-Drive Robot Vehicle.c
 *
 * Created: 9/4/2023 2:59:47 AM
 * Author : Mahmoud Ismail
 */ 

#include <avr/io.h>
#include <util/delay.h>

void PWM_init(void) {
	
	/* 
	1. Clear OC2A on compare match, set OC2A at BOTTOM,
	(non-inverting mode).
	2. Clear OC2B on compare match, set OC2B at BOTTOM,
	(non-inverting mode).
	3. Fast PWM 
	*/
	TCCR2A =  (1 << WGM20) | (1 << WGM21);
	
	/* Clear Reg TCNT */
	TCNT2 = 0x00;
	
	/* clkT2S/8 (from prescaler) */
	TCCR2B = (1<<CS21);
	
	/* Set OC2A/PB3 as output */
	DDRB |= (1<<PORTB3);
	
	/* Set OC2B/PD3 as output */
	DDRD |= (1<<PORTD3);
}

void motorInit(void) {
	
	/* Set Pins Direction */
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB4) | (1<<PORTB5); 
}

void moveForward(uint8_t duty)
{
	/* set direction */
	PORTB |= (1 << PORTB4)|(1 << PORTB1);   // PB4,1 HIGH
	PORTB &= ~(1 << PORTB5)&~(1 << PORTB2); // PB5,2 LOW
	
	/* Set speed */
	TCCR2A |= (1 << COM2A1); // PWM output on OCR2A - PB3
	TCCR2A |= (1 << COM2B1); // PWM to OCR2B - PD3
	OCR2A = duty;			// set PORTB3 to PWM value
	OCR2B = duty;            // set PORTD3 to PWM value
	
}

void moveBackward(uint8_t duty)
{
	/* set direction */
	PORTB &= ~(1 << PORTB4)&~(1 << PORTB1);  // PB4,1 LOW
	PORTB |= (1 << PORTB5)|(1 << PORTB2);   // PB5,2 HIGH
	
	/* set speed */
	TCCR2A |= (1 << COM2A1); // PWM output on OCR2A - PB3
	TCCR2A |= (1 << COM2B1); // PWM to OCR2B - PD3
	OCR2A = duty;			// set PORTB3 to PWM value
	OCR2B = duty;            // set PORTD3 to PWM value

}

void moveLeft(uint8_t duty)
{
	/* set direction */
	PORTB |= (1 << PORTB4)|(1 << PORTB2);   // PB4,2 HIGH
	PORTB &= ~(1 << PORTB5)&~(1 << PORTB1); // PB5,1 LOW
	
	/* set speed */
	TCCR2A |= (1 << COM2A1); // PWM output on OCR2A - PB3
	TCCR2A |= (1 << COM2B1); // PWM to OCR2B - PD3
	OCR2A = duty;			// set PORTB3 to PWM value
	OCR2B = duty;            // set PORTD3 to PWM value
	
}

void moveRight(uint8_t duty)
{
	/* set direction */
	PORTB |= (1 << PORTB5)|(1 << PORTB1);   // PB5,1 HIGH
	PORTB &= ~(1 << PORTB4)&~(1 << PORTB2); // PB4,2 LOW
	
	/* set speed */
	TCCR2A |= (1 << COM2A1); // PWM output on OCR2A - PB3
	TCCR2A |= (1 << COM2B1); // PWM to OCR2B - PD3
	OCR2A = duty;			// set PORTB3 to PWM value
	OCR2B = duty;            // set PORTD3 to PWM value
	
}

void motorsOff(void)
{
	TCCR2A &= ~(1 << COM2A1);	// disconnect PWM from OCR2A – PB3
	TCCR2A &= ~(1 << COM2B1);   // disconnect PWM from OCR2B – PD3
	PORTB &= ~(1 << PORTB3);    // set enable pins to zero for brake
	PORTD &= ~(1 << PORTD3);
}


int main(void)
{
    /* Replace with your application code */
	
	/* Init PWM */
	PWM_init();
	
	/* Init Motor */
	motorInit();
	
	_delay_ms(3000);
	
    while (1) 
    {
		moveForward(128);
		_delay_ms(2000);
		moveLeft(128);
		_delay_ms(2000);
		moveRight(128);
		_delay_ms(2000);
		motorsOff();
		moveBackward(128);
		_delay_ms(2000);
    }
}

