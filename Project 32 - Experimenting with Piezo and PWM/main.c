/*
 *  Project 32 - Experimenting with Piezo and PWM
 *
 * Created: 4/20/2023 6:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


/*------------------------------ Defines -------------------------------------*/

#define ADC_CHANNEL                2

/*---------------------------- Functions --------------------------------------*/

void ADC_init(void) {
	
	ADMUX = (1<<MUX1);     /* ADC Channel 2 PB4 */
	
	ADCSRA = (1<<ADEN) | (1<<ADPS0);              /* ADC Enable , Prescaler = 2 */
}

uint16_t ADC_read(void) {
	
	uint16_t ret_adc;
	
	ADCSRA |= (1<<ADSC);    /* Start ADC Conversation */
	
	while(BIT_IS_SET(ADCSRA,ADSC));     /* Loop until conversation is done  */
	
	ret_adc = ADC;                    /* Read data from ADC  */
	
	return ret_adc;           /* Return ADC Reading */
	
}

void PWM_init(void) {
	
	DDRB |= (1 << PORTB0); /* Set PB0 as output */
	
	TCCR0A = (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);           /* Set OC0A ,FAST PWM , Non Inverting Mode  */
	 
	TCCR0B = (1<<WGM02) | (1<<CS00);                /* No prescaler */
}


int main(void)
{
	uint16_t adc_to_timer;
	
	ADC_init();    /* Init ADC  */
	PWM_init();    /* Init PWM  */
	
	while(1)
	{
		adc_to_timer = (ADC_read() * 255) / 1024;  /* Convert 1024 adc reading to eqauvilent 256 timer */
		OCR0A = adc_to_timer;                      /* Set duty cycle */
		_delay_ms(10);
	}
	
	
}
