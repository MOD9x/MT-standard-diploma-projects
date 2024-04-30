/*
 * DcMotor.c
 *
 *  Created on: Feb 22, 2024
 *      Author: mod_n
 */

#include "gpio.h"
#include "common_macros.h"
#include "DcMotor.h"
#include"PWM.h"


void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DCMOTOR_PORT1,DCMOTOR_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_PORT2,DCMOTOR_PIN2, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_ENABLE_PORT,DCMOTOR_ENABLE_PIN, PIN_OUTPUT);

	/*
	 * configure Pin1 , Pin2 and enable pin as O/P pins
	 */

	GPIO_writePin(DCMOTOR_PORT1,DCMOTOR_PIN1, LOGIC_LOW );
	GPIO_writePin(DCMOTOR_PORT2,DCMOTOR_PIN2, LOGIC_LOW );
	GPIO_writePin(DCMOTOR_ENABLE_PORT,DCMOTOR_ENABLE_PIN, LOGIC_LOW );

	/*
	 * clearing Pin1 , Pin2 and enable pin ( Motor is OFF )
	 */
}

void DcMotor_Rotate( DcMotor_State state , uint8 speed)
{
	switch(state)
	{
	case 0 :
		GPIO_writePin(DCMOTOR_PORT1,DCMOTOR_PIN1, LOGIC_LOW );
		GPIO_writePin(DCMOTOR_PORT2,DCMOTOR_PIN2, LOGIC_LOW );

		break;
		/*
		 * clearing Pin1 , Pin2 ( Motor is OFF )
		 */

	case 1 :
			GPIO_writePin(DCMOTOR_PORT2,DCMOTOR_PIN2, LOGIC_HIGH );

			break;
			/*
			 * SET Pin2 ( Motor is ON Clockwise )
			 */

	case 2 :
			GPIO_writePin(DCMOTOR_PORT1,DCMOTOR_PIN1, LOGIC_HIGH );

			break;
			/*
			 * SET Pin1 ( Motor is ON Anti-Clockwise )
			 */

	}

	PWM_Timer0_Start(speed);
	/*
	 * calling PWM to Control the speed of the Motor
	 */
}
