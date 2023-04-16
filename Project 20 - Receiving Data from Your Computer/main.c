/* Author : Mahmoud Ismail */
/* Date   : 16/4/2023      */
/*  Project 20 - Receiving Data from Your Computer */


/*------------------------------ Includes -------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


/*-------------------------- Defines ------------------------------*/
#define  F_CPU                   1000000UL
#define  BAUD_RATE               4800
#define  BAUD_PRESCALER          ((F_CPU / (16UL*BAUD_RATE)) - 1)



/*-----------------------  Functions  ------------------------------*/


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


uint8_t UART_recieveByte(void) {
	
	uint8_t ret_byte;         /* Returnd Byte from UART  */
	
	/* Wait for data to be received */
	while(BIT_IS_CLEAR(UCSR0A,RXC0)); 
	
	/* Get and return received data from buffer */
	ret_byte = UDR0;
	return ret_byte;
}

void UART_recieveString(uint8_t *Str) {
	
	/* Counter for string array  */
	uint8_t i = 0;
	
	/* Recive First Char  */
	Str[i] = UART_recieveByte();
	
	/*  Loop Untill String ends */
	while(Str[i] != '\n')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	
	/* Put Terminating Char  */
	Str[i] = '\0';
}

int main(void) {
	
	UART_init();      /* Init UART  */
	uint8_t temp_byte;
	
	while(1)
	{
		temp_byte = UART_recieveByte();
		UART_sendByte(temp_byte);
		_delay_ms(500);
	}
	
	return 0;
}