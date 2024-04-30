/*
 * ADC.c
 *
 *  Created on: Feb 16, 2024
 *      Author: mod_n
 */

#include"ADC.h"

#include"common_macros.h"

#include<avr/io.h>

void ADC_init( const ADC_ConfigType * Config_Ptr )
{
	/*
	 * Vref selection
	 */
	ADMUX = (Config_Ptr->ref_volt);

	ADCSRA = (Config_Ptr->prescaler) | (1<<ADEN);
	/* pre-scaler selection and ADC module enabled */

}

uint16 ADC_readChannel( uint8 ch_num)
{
	/*
	 * channel selection
	 */
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x07) ;

	/*
	 * start conversion
	 */
	SET_BIT(ADCSRA,ADSC);

	/*
	 * polling until conversion is complete
	 */
	while( BIT_IS_CLEAR(ADCSRA,ADIF) );

	/*
	 * clearing the flag
	 */
	SET_BIT(ADCSRA,ADIF);
	/*
	 * read value of conversion
	 */
	return ADC;
}

