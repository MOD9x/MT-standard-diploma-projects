/*
 * PWM.c
 *
 *  Created on: Feb 22, 2024
 *      Author: mod_n
 */

#include<avr/io.h>
#include "gpio.h"
#include "common_macros.h"
#include"PWM.h"


void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01) ;
	/*
	 *      MODE : FAST PWM | NON-INVERTING | N=8
	 */

	TCNT0=0; // initial value

	OCR0= (duty_cycle * (2.55) );
	/*

	(this equation to convert duty cycle to OCR0 value)

	 duty cycle = 0% - 100% , OCR0 = 0-255

	 */

}
