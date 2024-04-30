/*
 * UART.h
 *
 *  Created on: Mar 6, 2024
 *      Author: mod_n
 */

#ifndef UART_H_
#define UART_H_

#include"std_types.h"

/******************************  Definitions  ************************************************************************/

#define UART_BaudRate uint8


/******************************  Types Declaration   *****************************************************************/

typedef enum
{
	UART_NORMAL,UART_DOUBLE
}UART_transmissionSpeed;

typedef enum
{
	UART_ASYNCHRONOUS,UART_SYNCHRONOUS
}UART_modeSelcetion;

typedef enum
{
	UART_5bits,UART_6bits,UART_7bits,UART_8bits,UART_9bits=7
}UART_BitData;

typedef enum
{
	UART_parityDisabled,UART_parityEven=2,UART_parityOdd
}UART_Parity;

typedef enum
{
	UART_1StopBit,UART_2StopBits
}UART_StopBit;



typedef struct
{
	UART_BitData bit_data;

	UART_Parity parity;

	UART_StopBit stop_bit;

	UART_BaudRate baud_rate;

}UART_ConfigType;


/*****************************  Functions Prototypes  ****************************************************************/

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
void UART_init( const UART_ConfigType * Ptr_Configs );

/*
 * Description :
 * Function for sending byte to another device by using UART .
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Function for receive byte from another device by using UART .
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Function for sending string to another device by using UART .
 */
void UART_sendString( const uint8 * a_Str);

/*
 * Description :
 * Function for receive string from another device by using UART .
 */
void UART_receiveString( uint8 * a_Str );

/*
 * Description :
 * Function for receive string from another device by using UART
 * That string will be sending again to another device by using UART
 */
void UART_receiveStringBacktoBack( uint8 * a_Str );

/*
 * Description :
 * Function for sending array to another device by using UART .
 */
void UART_sendArray( const uint8 * a_array ,uint8 a_size );
/*
 * Description :
 * Function for receive array from another device by using UART .
 */
void UART_receiveArray( uint8 * a_array ,uint8 a_size );


#endif /* UART_H_ */
