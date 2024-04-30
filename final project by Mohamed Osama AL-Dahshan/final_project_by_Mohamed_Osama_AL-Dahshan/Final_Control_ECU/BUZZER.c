/*
 * BUZZER.c
 *
 *  Created on: Mar 25, 2024
 *      Author: mod_n
 */

#include"gpio.h"
#include"BUZZER.h"

/*
 * Description : function for initiate the Buzzer by :
 * 1. Setup pin Direction .
 * 2. Turn off the buzzer .
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID , DCMOTOR_PIN_ID , PIN_OUTPUT);

	GPIO_writePin(BUZZER_PORT_ID , DCMOTOR_PIN_ID , LOGIC_LOW);

}

/*
 * Description : function for turn on the buzzer .
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID , DCMOTOR_PIN_ID , LOGIC_HIGH);

}

/*
 * Description : function for turn off the buzzer .
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID , DCMOTOR_PIN_ID , LOGIC_LOW);

}

