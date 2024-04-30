/*
 * EEPROM.h
 *
 *  Created on: Mar 22, 2024
 *      Author: mod_n
 */

#ifndef EEPROM_H_
#define EEPROM_H_


#include"std_types.h"

/***************************************** Definitions ***************************************************************/

#define ERROR 0
#define SUCCESS 1

/***************************************** Types declarations ********************************************************/

/***************************************** Functions prototype *******************************************************/


/*
 * Description :
 * Function for sending byte to EEPROM device by using I2C .
 */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);

/*
 * Description :
 * Function for receiving byte from EEPROM device by using I2C .
 */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

void EEPROM_writeArray(uint16 frist_address,const uint8 * a_array , uint8 size);

void EEPROM_readArray(uint16 frist_address,const uint8 * a_array , uint8 size);


#endif /* EEPROM_H_ */
