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
#include <stdlib.h>
#include "common_macros.h"

/*-------------------------- Global Variables -------------------------------*/

volatile uint8_t counter ;

/*-------------------------- Defines ------------------------------*/
#define  F_CPU                   1000000UL
#define  BAUD_RATE               4800
#define  BAUD_PRESCALER          ((F_CPU / (16UL*BAUD_RATE)) - 1)



/*------------------------------- ISR's ------------------------------------*/
ISR(INT0_vect) {
	
	counter ++;
	
	SET_BIT(EIFR,INTF0);  /* Clear Flag  */
}

ISR(INT1_vect) {
	
	counter --;
	
	SET_BIT(EIFR,INTF1);  /* Clear Flag  */
}
	
/*-------------------------- Functions ----------------------------------*/

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

void UART_sendString(uint8_t *String) {
	
	while(*String != '\0')          /* Loop untill string is end  */
	{
		UART_sendByte(*String);     /* Send one byte of data      */
		String++;                   /* Increment Counter         */
	}
}
	

int main(void)
{
	
	CLEAR_BIT(DDRD,PD2);  /* Set INT0 pin as INPUT  */
	
	CLEAR_BIT(DDRD,PD3);  /* Set INT1 pin as INPUT  */
	
	EICRA = 0x0B;          /* The falling edge of INT1 generates an interrupt request , The rising edge of INT0 generates an interrupt request */
	
	SET_BIT(EIMSK,INT0);   /* Enable INT0 */
	
	SET_BIT(EIMSK,INT1);   /* Enable INT1 */
	
	sei();                 /* Enable Global Intterupt */
	
	UART_init();           /* Initliaze UART  */
	
	uint8_t counterArray[4];  /* Array to hold counter value and send it over UART */
	
	while(1)
	{
		itoa(counter, counterArray, 10);  /* Convert Counter to array of string */
		UART_sendString("Conuter = ");   
		UART_sendString(counterArray);    /* Send Counter  */
		UART_sendString("\r\n");          /* Start New line  */
		_delay_ms(500);
	}
	
}
