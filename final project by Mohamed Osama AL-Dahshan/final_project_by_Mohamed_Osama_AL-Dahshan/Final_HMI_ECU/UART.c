/*
 * UART.c
 *
 *  Created on: Mar 6, 2024
 *      Author: mod_n
 */

#include"UART.h"

#include "common_macros.h"

#include "gpio.h"

#include<avr/io.h>

/* Description :
 * Function for initialize the UART device by :
 * 1. Setup the UART transmission speed .
 * 2. Setup the UART mode .
 * 3. Setup the UART character Size .
 * 4. Setup the UART parity type .
 * 5. Setup the UART number of stop bits .
 * 6. Setup the UART baud rate .
 * 7.Enable the UART mask flags .
 */
void UART_init( const UART_ConfigType * Ptr_Configs )
{
	uint16 ubrr_value = 0;

	UCSRA = (1<<U2X) ;
	/*	Configure the transmission speed which is double in Asynchronous mode only */

	UCSRB = (1<<RXEN) |(1<<TXEN) |  (Ptr_Configs->bit_data & 4) ;
	/* Receive Complete Interrupt and Data Register Empty Interrupt enabled
	 Receiver and  Transmitter Enabled , UCSZ2 is bit number 3 in the register which is also
	 bit number 3 in the Character size ( Character Size ANDing with 0000 0100 to get the 3rd bit ) */

	UCSRC = ( Ptr_Configs->parity <<UPM0) | (Ptr_Configs->stop_bit<<USBS)
			| ( ( Ptr_Configs->bit_data & 3) << UCSZ0 ) ;
	/*	Mode selection ( synchronous or asynchronous )and partiy (disabled , even or odd)
	 *	And stop bit ( 1 bit or 2 bits) and the rest 2 bits of the Character size UCSZ0 and UCSZ1
	 *  ( Character Size ANDing with 0000 0011 to get the 1st 2 bits )
	 */

	ubrr_value = (uint16)(((F_CPU / (Ptr_Configs->baud_rate * 8UL))) - 1);
	/* Calculate the UBRR register value */


	UBRRH = ( ubrr_value>>8 );
	UBRRL = ubrr_value;
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH
	 * Because they are not consecutive */
}

/*
 * Description :
 * Function for sending byte to another device by using UART .
 */
void UART_sendByte( const uint8 data)
{
	while( BIT_IS_CLEAR(UCSRA,UDRE) ){}
	/*	Polling to check that data register is clear ( no operation is going on )
	 * 	UDRE flag is set when the Tx buffer (UDR) is empty
	 */

	UDR=data;
	/*	Transfer the data from the memory to the data register */

}

/*
 * Description :
 * Function for receive byte from another device by using UART .
 */
uint8 UART_receiveByte(void)
{
	while( BIT_IS_CLEAR(UCSRA,RXC) ){}
	/*	Polling to check that receive register is full and unread
	 *  RXC flag is set when the UART receiving data is done
	 */

	return UDR;
	/*	Transfer the data from the data register to the memory */

}

/*
 * Description :
 * Function for sending string to another device by using UART .
 */
void UART_sendString( const uint8 * a_Str)
{
	while( *a_Str != '\0' )
	{
		UART_sendByte( *a_Str );
		a_Str++;
	}
	/*	Looping on the string with sending it byte by byte
	 *  By calling UART_sendByte function every iteration
	 */
}

/*
 * Description :
 * Function for receive string from another device by using UART .
 */
void UART_receiveString( uint8 * a_Str )
{

	*a_Str=UART_receiveByte();

	while( *a_Str != '#' )
	{
		a_Str++;

		*a_Str=UART_receiveByte();
	}
	/*	Looping on the string until '#' with receiving
	 *  It byte by byte by calling UART_receiveByte function
	 *  Every iteration and save it in the array
	 */

	*a_Str = '\0';
	/* After receive the array we replace the '#' with '\0' because its string */
}

/*
 * Description :
 * Function for receive string from another device by using UART
 * That string will be sending again to another device by using UART
 */
void UART_receiveStringBacktoBack( uint8 * a_Str )
{
	*a_Str=UART_receiveByte();

	while( *a_Str != '#' )
	{
		a_Str++;

		*a_Str=UART_receiveByte();
	}

	a_Str++;

	*a_Str = '\0';
}

/*
 * Description :
 * Function for sending array to another device by using UART .
 */
void UART_sendArray( const uint8 * a_array ,uint8 a_size )
{
	uint8 counter = 0 ;

	/* Looping to send the array */
	while( counter < a_size )
	{
		UART_sendByte(a_array[counter]) ;

		counter++;
	}
}

/*
 * Description :
 * Function for receive array from another device by using UART .
 */
void UART_receiveArray( uint8 * a_array ,uint8 a_size )
{
	uint8 counter = 0 ;

	/* Looping to send the array */
	while( counter < a_size )
	{
		a_array[counter] = UART_receiveByte() ;

		counter++;
	}
}




