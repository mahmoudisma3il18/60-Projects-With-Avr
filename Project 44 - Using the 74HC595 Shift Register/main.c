/*
 * Author : Mahmoud Ismail
 * Date : 1/5/2023
 * Project 44 - Using the 74HC595 Shift Register
 */
 
 
#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"


/*-------------------------------- Global Vars ------------------------------------------*/

uint8_t SevenSegment_Display[] = { 0b11111100,   /* 0 */
                                   0b01100000,   /* 1 */
								   0b11011010,   /* 2 */
								   0b11110010,   /* 3 */
								   0b01100110,   /* 4 */
								   0b10110110,   /* 5 */
								   0b10111110,   /* 6 */
								   0b11100000,   /* 7 */
								   0b11111110,   /* 8 */
								   0b11100110    /* 9 */ 
								   };
								   
								   


/*------------------------------ Functions ----------------------------------------------*/

void SPI_init(void) {
	
	/* Set MOSI and SCK output and SS, all others input */
    DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB0);
	DDRB &= ~(1<<PB4);
	
	PORTB |= (1 << PB0); // SS pin HIGH
	
    /* Enable SPI, Master, set clock rate fck/4 , LSB of the data word is transmitted first */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<DORD);
	
}

void SPI_sendByte(uint8_t data) {
	
	/* Start transmission */
    SPDR = data;
    /* Wait for transmission complete */
    while(BIT_IS_CLEAR(SPSR,SPIF));
}


int main(void) {
	
	SPI_init();    /* Init SPI  */
	
	uint8_t i;
	
	while(1) 
	{
		for(i = 0 ; i < 10 ; i++)
			{
				CLEAR_BIT(PORTB,PB0);   /* SS Low */ 
		
		        SPI_sendByte(SevenSegment_Display[i]); /* Send Data */
		
		        SET_BIT(PORTB,PB0);   /* SS High */
				
				_delay_ms(1000);
	        }
	}
	
	return 0;
}

