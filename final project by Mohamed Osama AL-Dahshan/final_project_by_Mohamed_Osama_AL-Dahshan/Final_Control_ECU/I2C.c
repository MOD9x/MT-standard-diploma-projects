/*
 * I2C.c
 *
 *  Created on: Mar 21, 2024
 *      Author: mod_n
 */

#include "I2C.h"
#include<avr/io.h>
#include"common_macros.h"

/*
 * description :
 * function for initialize TWI module by :
 * 1.setup the TWI bit rate .
 * 2.setup the TWI address .
 * 3.enable the TWI module .
 * note : we configured TWI pre-scaler = 1 which is default
 * 		  so we didn't need to initialize that .
 */
void TWI_init( const TWI_ConfigType * Config_Ptr )
{
	TWBR = Config_Ptr->bit_rate;
	/* configure TWI bit rate by initialize ( TWBR ) register */

	TWAR = (Config_Ptr->address<<1);
	/* configure address by initialize ( TWAR ) register */

	TWCR = (1<<TWEN)  ;
	/* TWI module enabled by setting ( TWEN ) bit */
}

/*
 * description : function for starting TWI operation .
 */
void TWI_start(void)
{
	TWCR = (1<<TWEN) | (1<<TWSTA) | (1<<TWINT);
	/*
	 * 1.TWI module enabled by setting ( TWEN ) bit.
	 * 2.TWI start operation enabled by setting ( TWSTA ) bit.
	 * 3.TWI flag cleared by setting ( TWINT ) bit.
	 */

	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
	/* polling to make sure start operation completed by checking TWI flag ( TWINT ) bit */
}

/*
 * description : function for stopping TWI operation .
 */
void TWI_stop(void)
{
	TWCR = (1<<TWEN) | (1<<TWSTO) | (1<<TWINT);
	/*
	 * 1.TWI module enabled by setting ( TWEN ) bit.
	 * 2.TWI stop operation enabled by setting ( TWSTO ) bit.
	 * 3.TWI flag cleared by setting ( TWINT ) bit.
	 */
}

/*
 * Description :
 * Function for sending byte to another device by using I2C .
 */
void TWI_writeByte( uint8 data )
{
	TWDR = data ;
	/*	Transfer the data from the memory to the data register .
	 * 	note : TWDR contains the next byte to be transmitted or received .
	 */

	TWCR = (1<<TWEN) | (1<<TWINT);
		/*
		 * 1.TWI module enabled by setting ( TWEN ) bit.
		 * 2.TWI flag cleared by setting ( TWINT ) bit.
		 */
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
	/* polling to make sure sending operation completed by checking TWI flag ( TWINT ) bit */
}

/*
 * Description :
 * Function for receiving byte from another device by using I2C .
 */
uint8 TWI_readByteWithACK( void )
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
		/*
		 * 1.TWI module enabled by setting ( TWEN ) bit.
		 * 2.TWI flag cleared by setting ( TWINT ) bit.
		 * 3.TWI Ack enabled by setting ( TWEA ) bit.
		 */
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
	/* polling to make sure receiving operation completed by checking TWI flag ( TWINT ) bit */

	return TWDR ;
	/*	Transfer the data from the data register to the memory.
	 * 	note : TWDR contains the next byte to be transmitted or received .
	 */
}

/*
 * Description :
 * Function for receiving byte from another device by using I2C .
 * note : ( only for master ) to end communication with slave.
 */
uint8 TWI_readByteWithNACK( void )
{
	TWCR = (1<<TWEN) | (1<<TWINT) ;
		/*
		 * 1.TWI module enabled by setting ( TWEN ) bit.
		 * 2.TWI flag cleared by setting ( TWINT ) bit.
		 */
	while( BIT_IS_CLEAR(TWCR,TWINT) ){}
	/* polling to make sure receiving operation completed by checking TWI flag ( TWINT ) bit */

	return TWDR ;
	/*	Transfer the data from the data register to the memory.
	 * 	note : TWDR contains the next byte to be transmitted or received .
	 */
}

/*
 * Description :
 * Function for receiving the status of the TWI module .
 */
uint8 TWI_getStatus( void )
{
	uint8 status ;

	status = ( TWSR & 0xF8 ) ;
	/* masking to get status bits which are the last 5 bits of TWSR register */

	return status ;
}
