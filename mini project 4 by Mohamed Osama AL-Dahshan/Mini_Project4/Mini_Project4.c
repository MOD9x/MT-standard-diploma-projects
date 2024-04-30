/*
 * Mini_Project4.c
 *
 *  Created on: Mar 4, 2024
 *      Author: mod_n
 */

#include"LCD.h"

#include "gpio.h"

#include"Ultrasonic.h"

#include<avr/io.h>

#include <util/delay.h>



int main()
{
	uint16 totalDistance=0;

	Ultrasonic_init();
	/* Ultrasonic initialization */

	LCD_init();
	/* LCD initialization */

	SREG |= (1<<7);
	/*I-bit enabled */

	LCD_displayString("Distance =    cm");

	while(1)
	{
		totalDistance = Ultrasonic_readDistance()+1;
		/* +1 : sensor has error with 1 cm */


		LCD_intgerToStringRowColumn(0,11,totalDistance);
		/* Distance display */

		if( totalDistance == 9)
		{
			LCD_displayCharacterRowColumn(0,12,' ');
		}

		else if( totalDistance == 99)
		{
			LCD_displayCharacterRowColumn(0,13,' ');
		}

		/* to clear the extra digit remaining */

	}
}
