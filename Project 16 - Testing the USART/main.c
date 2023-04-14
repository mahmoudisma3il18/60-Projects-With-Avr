/* Author : Mahmoud Ismail */
/* Date   : 14/4/2023      */
/* Project 16: Testing the USART */


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

int main(void) {
	
	UART_init();      /* Init UART  */
	
	while(1)
	{
		UART_sendString("Hello World");    /* Send String   */
		_delay_ms(1000);                   /* Delay for 1 Sec */
	}
	
	return 0;
}