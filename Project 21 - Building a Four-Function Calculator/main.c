/*
 * Simple Calculator.c
 *
 * Created: 4/16/2023 5:01:55 PM
 * Author : Mahmoud Ismail
 */ 


/*-------------------------------- Includes ---------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Include the header file for the UART interface */
#include "uart.h"

int main(void)
{
	/* Initialize UART with Baud Rate 4800 */
	UART_init(BaudRate_4800);
	
	/* Define variables for the two digits, the operator, a flag for continuing the program, and a float variable for the result of the operation */
	uint8_t digit1, digit2, operator, flag;
	float result = 0;
	uint8_t result_array[8];
	
	/* Use a do-while loop to repeatedly prompt the user for two digits and an operator, perform the operation, display the result, and ask the user if they want to perform another operation */
	do
	{
		/* Prompt the user to enter the first digit */
		UART_sendString("Enter First Digit: ");
		digit1 = UART_recieveByte();
		
		/* Echo the first digit back to the terminal */
		UART_sendByte(digit1);
		UART_sendString("\r\n");
		
		/* Prompt the user to enter the second digit */
		UART_sendString("Enter Second Digit: ");
		digit2 = UART_recieveByte();
		
		/* Echo the second digit back to the terminal */
		UART_sendByte(digit2);
		UART_sendString("\r\n");
		
		/* Prompt the user to enter the operator */
		UART_sendString("Enter Operator (+,-,*,/): ");
		operator = UART_recieveByte();
		
		/* Echo the operator back to the terminal */
		UART_sendByte(operator);
		UART_sendString("\r\n");
		
		/* Convert the character inputs for the digits and operator into integer and float values */
		digit1 = digit1 - 0x30;
		digit2 = digit2 - 0x30;
		
		/* Use a switch statement to perform the selected operation on the two integer values and store the result in a float variable */
		switch(operator)
		{
			case '+' :
			result = (float)digit1 + (float)digit2;
			break;
			
			case '-' :
			result = (float)digit1 - (float)digit2;
			break;
			
			case '*' :
			result = (float)digit1 * (float)digit2;
			break;
			
			case '/' :
			result = (float)digit1 / (float)digit2;
			break;
			
			default:
			UART_sendString("Enter Right Operator\r\n");
			break;
		}
		
		/* Convert the float result into a character array using the "dtostrf" function with two decimal places */
		dtostrf(result, 5, 2, result_array);
		
		/* Display the result on the terminal */
		UART_sendString("Result: ");
		UART_sendString(result_array);
		UART_sendString("\r\n");
		
		/* Prompt the user to continue the program by entering 'y' or 'n' */
		UART_sendString("Do you want to do another operation (y / n)? ");
		flag = UART_recieveByte();
		
		/* Echo the flag back to the terminal */
		UART_sendByte(flag);
		UART_sendString("\r\n");
		
	} while (flag == 'y');
	
	/* Return 0 to indicate successful execution of the program */
	return 0;
}
