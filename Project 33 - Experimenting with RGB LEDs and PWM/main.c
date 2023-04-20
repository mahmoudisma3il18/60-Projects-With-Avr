/*
 * Project 33 - Experimenting with RGB LEDs and PWM
 * Created: 4/20/2023 5:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"




void PWM_init(void) {
	
	/* Timer 1 (OC1A/OC1B) Config. */
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);     /* Fast PWM , Non Inverting */

	TCCR1B |= (1<<CS10) | (1<<WGM12);                 /* No PreScaler */
	
	/* Timer 2 (OCR2A - PB3) Config. */
	
	TCCR2A = (1<<COM2A1) | (1<<WGM20) | (1<<WGM21);   /* Fast PWM Mode, (non-inverting mode) */
	
	TCCR2B =  (1<<CS20);                  /* No Prescaler */
}

void PWMblue(uint8_t duty)
// Blue LED is on PB1
{
    OCR1A = duty;
}

void PWMred(uint8_t duty)
// Red LED is on PB3
{
    OCR2A = duty;
}

void PWMgreen(uint8_t duty)
// Green LED is on PB2
{
    OCR1B = duty;
}

int main(void)
{
	DDRB = (1<<PB1) | (1<<PB2) | (1<<PB3);   /* Set PB1,PB2 and PB3 as Output */
	
	PWM_init();
	
	uint8_t a;
	
	
	while(1)
	{
		
		  // red to green
	     for (a=1; a<255; a++)
	    {
           PWMred(255-a);
           PWMgreen(a);
           _delay_ms(20);
        }
	
        // green to blue
        for (a=1; a<255; a++)
        {
            PWMgreen(255-a);
            PWMblue(a);
            _delay_ms(20);
	    }
	
	    // blue to red
	    for (a=1; a<255; a++)
	    {
            PWMblue(255-a);
            PWMred(a);
            _delay_ms(20);	
        }
	}
}
