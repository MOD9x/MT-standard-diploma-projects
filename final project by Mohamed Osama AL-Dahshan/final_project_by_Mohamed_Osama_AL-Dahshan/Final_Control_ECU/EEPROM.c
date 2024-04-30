/*
 * EEPROM.c
 *
 *  Created on: Mar 22, 2024
 *      Author: mod_n
 */

#include"EEPROM.h"
#include"I2C.h"
#include <util/delay.h>


/*
 * Description :
 * Function for sending byte to EEPROM device by using I2C .
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* write byte to eeprom */
    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}

/*
 * Description :
 * Function for receiving byte from EEPROM device by using I2C .
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}

void EEPROM_writeArray(uint16 frist_address,const uint8 * a_array , uint8 size)
{
	uint8 counter=0;

	while(counter <= (size-1) )
	{
		EEPROM_writeByte( ( counter + frist_address ) , a_array[counter]);

		counter++;

		_delay_ms(10);

	}
}

void EEPROM_readArray(uint16 frist_address,const uint8 * a_array , uint8 size)
{
	uint8 counter=0;

	while(counter <= (size-1) )
	{
		EEPROM_readByte( ( counter + frist_address ) , (a_array+counter) );

		counter++;

		_delay_ms(10);

	}
}
