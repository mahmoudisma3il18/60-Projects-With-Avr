/*
 * Project 35 - Temperature-Controlled Fan
 * Created: 1/9/2023 1:01:55 AM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


#define  F_CPU          1000000

volatile 	uint16_t temperature;


/* Initiliaze PWM with Timer1 PinB6 - OC1A */
void PWM_init(void) {
	
	/* 
	   1. Clear OC1A on compare match, set OC1A at 
       BOTTOM (non-inverting mode)
	   2. Fast PWM, 8-bit
       3. clkI/O/1 (no prescaling)	
       4. Set PB1 as Output	   
	*/
	TCCR1A |= (1<<COM1A1) | (1<<WGM10); 
    TCCR1B |= (1<<WGM12) | (1<<CS10);
	DDRB   |= (1<<PB1);

}

void PWM_setDutyCycle(uint8_t duty_cycle) {
	
	/* 
	   1. Set duty cycle
	*/
	OCR1A = duty_cycle & 0xFF;  
	
}


void ADC_init(void) {
	
	/*
	1. AVCC with external capacitor at AREF pin
	2. Enable ADC5
	3. Set F_CPU / 8
	4. Enable ADC
	5. Set PC5 as Input
	*/
	
	ADMUX  |= (1<<REFS0);
	ADMUX  |= (1<<MUX0) | (1<<MUX2);
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
	ADCSRA |= (1<<ADEN);
	//DDRC   &= ~(1<<PC5);
}


uint16_t ADC_readVoltage(void) {
	
	/* Varaible to hold returned value */
	uint16_t ret_value = 0;  
	
	/* Start Conversation */
	ADCSRA |= (1<<ADSC);
	
	/* Loop untill conversatin is done */
	while(BIT_IS_SET(ADCSRA,ADSC));
	
	/* Return Value */
	ret_value = ADC;
	
	return ret_value;
	
}	


int main (void) {
	
	
	/* Init PWM */
	PWM_init();
	
	/* Init ADC */
	ADC_init();
	
	
	while(1) {
		
		/* Read Temperature */
	    
		temperature = (uint16_t)(((uint32_t)ADC_readVoltage()*125*5.0)/(1024*1.25)) - 50; // Minus -50 because we are in room temp
		
		/* Set Motor Speed */
		
		if (temperature < 25 )
			PWM_setDutyCycle(0);    /* Turn Motor OFF */
		else if(temperature < 35 )
			PWM_setDutyCycle(127);  /* Half Speed */
		else if(temperature >= 35)
			PWM_setDutyCycle(255);  /* Full speed */
		
	}
	
	return 0;
	
}
	