/*
 * LM35.h
 *
 *  Created on: Feb 24, 2024
 *      Author: mod_n
 */

#ifndef LM35_H_
#define LM35_H_

#include"std_types.h"

/* ************************************** Definitions ***************************************************** */


#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/* **************************************  Types Declaration ***************************************************** */


 /* ************************************** Prototypes ***************************************************** */

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_GetTemperature(void);


#endif /* LM35_H_ */
