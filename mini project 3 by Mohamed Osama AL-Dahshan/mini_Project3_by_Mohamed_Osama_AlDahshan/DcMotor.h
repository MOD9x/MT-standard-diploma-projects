/*
 * DcMotor.h
 *
 *  Created on: Feb 22, 2024
 *      Author: mod_n
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/* ************************************** Definitions ***************************************************** */

#define DCMOTOR_PORT1 PORTB_ID

#define DCMOTOR_PIN1 PIN0_ID

#define DCMOTOR_PORT2 PORTB_ID

#define DCMOTOR_PIN2 PIN1_ID

#define DCMOTOR_ENABLE_PORT PORTB_ID

#define DCMOTOR_ENABLE_PIN PIN3_ID

/* **************************************  Types Declaration ***************************************************** */


typedef enum
{
	DC_MOTOR_STOP,DC_MOTOR_CW,DC_MOTOR_ACW
}DcMotor_State;


 /* ************************************** Prototypes ***************************************************** */

void DcMotor_Init(void);

void DcMotor_Rotate( DcMotor_State state , uint8 speed);


#endif /* DCMOTOR_H_ */
