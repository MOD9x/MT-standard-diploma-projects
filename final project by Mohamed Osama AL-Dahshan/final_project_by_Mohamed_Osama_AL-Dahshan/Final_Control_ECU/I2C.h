/*
 * I2c.h
 *
 *  Created on: Mar 21, 2024
 *      Author: mod_n
 */

#ifndef I2C_H_
#define I2C_H_

#include"std_types.h"

/***************************************** Definitions ***************************************************************/

#define TWI_Address uint8

#define TWI_BoudRate uint8

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/***************************************** Types declarations ********************************************************/

/*typedef enum
{
	TWI_PRESCALER_1,TWI_PRESCALER_4,TWI_PRESCALER_16,TWI_PRESCALER_64
}TWI_PRESCALER;*/

typedef struct
{
	/*TWI_PRESCALER pre-caler;*/

	TWI_Address		  address;

	TWI_BoudRate		  bit_rate;

}TWI_ConfigType;


/***************************************** Functions prototype *******************************************************/

/*
 * description :
 * function for initialize TWI module by :
 * 1.setup the TWI bit rate .
 * 2.setup the TWI address .
 * 3.enable the TWI module .
 * note : we configured TWI pre-scaler = 1 which is default
 * 		  so we didn't need to initialize that .
 */
void TWI_init( const TWI_ConfigType * Config_Ptr );

/*
 * description : function for starting TWI operation .
 */
void TWI_start(void);

/*
 * description : function for stopping TWI operation .
 */
void TWI_stop(void);

/*
 * Description :
 * Function for sending byte to another device by using I2C .
 */
void TWI_writeByte( uint8 data );

/*
 * Description :
 * Function for receiving byte from another device by using I2C .
 */
uint8 TWI_readByteWithACK( void );

/*
 * Description :
 * Function for receiving byte from another device by using I2C .
 * note : ( only for master ) to end communication with slave.
 */
uint8 TWI_readByteWithNACK( void );

/*
 * Description :
 * Function for receiving the status of the TWI module .
 */
uint8 TWI_getStatus( void );


#endif /* I2C_H_ */
