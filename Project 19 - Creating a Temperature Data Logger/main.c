/* Author : Mahmoud Ismail */
/* Date   : 14/4/2023      */
/*  Project 19 - Creating a Temperature Data Logger */


/*------------------------------ Includes -------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "common_macros.h"


/*-------------------------- Defines ------------------------------*/
#define  F_CPU                   1000000UL
#define  BAUD_RATE               4800
#define  BAUD_PRESCALER          ((F_CPU / (16UL*BAUD_RATE)) - 1)



/*-----------------------  Functions  ------------------------------*/

void ADC_init(void) {
	
	ADMUX  |= (1<<REFS0)|(1<<MUX0) | (1<<MUX2) ; //Use AVcc pin with ADC, Enable ADC5 (PC5)
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) ; // Enable ADC , Set prescaler to 1Mhz
}

uint16_t readAdc(void) {
	
	uint16_t retValue;
	
	ADCSRA |= (1<<ADSC); // Start ADC conversation
	
	while (BIT_IS_SET(ADCSRA,ADSC)); // Loop until ADC finish conversation 
	
	retValue = ADC;
	
	return retValue;
}


void UART_init(void) {
	
	/*   Set Baud Rate   */
	UBRR0H = (uint8_t)((BAUD_PRESCALER) >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALER);
	
	/*   Enable Reciver and Transmitter   */
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	
    /*   Set Frame format and mode :
    1.Asynchronus USART
    2.No parity bit	
	3.1 Stop Bit         
    4.8 bits data               	*/
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}


void UART_sendByte(uint8_t data) {
	
	/* Wait for empty transmit buffer */
	while(BIT_IS_CLEAR( UCSR0A,UDRE0));
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

UART_sendString(uint8_t *String) {
	
	while(*String != '\0')          /* Loop untill string is end  */
	{
		UART_sendByte(*String);     /* Send one byte of data      */
		String++;                   /* Increment Counter         */
	}
}

int main(void) {
	
	UART_init();      /* Init UART  */
	ADC_init();       /* Init ADC    */
	
	
	float temp,voltage;
	uint8_t array_of_temp[20];
	
	while(1)
	{    
        /*   Convert ADC Reading to Temp   */
		voltage = readAdc() * 5;        
		voltage = voltage / 1024.0;
		temp =  ((voltage - 0.5) * 100);
		
		/*  Send String   */
		UART_sendString("Temperature : ");
		
		/*  Convert Float to array of chars  */
		dtostrf(temp, 4, 1, array_of_temp);
		
		/* Send Temp */
		UART_sendString(array_of_temp);
		UART_sendString(" \r\n");
		_delay_ms(1000);
		
	}
	
	return 0;
}