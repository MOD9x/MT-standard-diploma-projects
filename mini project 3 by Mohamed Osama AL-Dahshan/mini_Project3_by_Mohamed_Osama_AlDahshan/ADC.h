/*
 * ADC.h
 *
 *  Created on: Feb 16, 2024
 *      Author: mod_n
 */




#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"

/* ************************************** Definitions ***************************************************** */

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56


/* **************************************  Types Declaration ***************************************************** */

typedef enum
{
	AREF_ADC,AVCC_ADC=64,InternalVref_ADC=	192
}ADC_ReferenceVoltage;

typedef enum
{
	ADC_F2,ADC_F4=2,ADC_F8=3,ADC_F16,ADC_F32,ADC_F64,ADC_F128
}ADC_Prescaler;


typedef struct
{
	ADC_ReferenceVoltage ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

 /* ************************************** Prototypes ***************************************************** */

void ADC_init( const ADC_ConfigType * Config_Ptr);

uint16 ADC_readChannel( uint8 ch_num);

#endif /* ADC_H_ */
