/*
 * DcMotor.c
 *
 *  Created on: Feb 22, 2024
 *      Author: mod_n
 */

#include "gpio.h"
#include "DcMotor.h"
#include"PWM.h"


void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DCMOTOR_INT1_PORT,DCMOTOR_INT1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_INT2_PORT,DCMOTOR_INT2_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_ENABLE1_PORT,DCMOTOR_ENABLE1_PIN, PIN_OUTPUT);

	/*
	 * configure input1 , input2 and enable pin as O/P pins
	 */

	GPIO_writePin(DCMOTOR_INT1_PORT,DCMOTOR_INT1_PIN, LOGIC_LOW );
	GPIO_writePin(DCMOTOR_INT2_PORT,DCMOTOR_INT2_PIN, LOGIC_LOW );
	/*
	 * clearing input1 and input2 pins ( Motor is OFF )
	 */

	GPIO_writePin(DCMOTOR_ENABLE1_PORT,DCMOTOR_ENABLE1_PIN, LOGIC_LOW );
	/* Clearing the enable1 pin */

}

void DcMotor_Rotate( DcMotor_State state , DcMotor_dutyCylce duty_cycle)
{
	switch(state)
	{
	case 0 :
		GPIO_writePin(DCMOTOR_INT1_PORT,DCMOTOR_INT1_PIN, LOGIC_LOW );
		GPIO_writePin(DCMOTOR_INT2_PORT,DCMOTOR_INT2_PIN, LOGIC_LOW );

		break;
		/*
		 * clearing input1 and input2 ( Motor is OFF )
		 */

	case 1 :
			GPIO_writePin(DCMOTOR_INT2_PORT,DCMOTOR_INT2_PIN, LOGIC_HIGH );

			break;
			/*
			 * SET input2 ( Motor is ON Clockwise )
			 */

	case 2 :
			GPIO_writePin(DCMOTOR_INT1_PORT,DCMOTOR_INT1_PIN, LOGIC_HIGH );

			break;
			/*
			 * SET input1 ( Motor is ON Anti-Clockwise )
			 */

	}

	PWM_Timer0_Start(duty_cycle);

}
