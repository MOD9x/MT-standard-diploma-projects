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

#define DCMOTOR_INT1_PORT PORTD_ID

#define DCMOTOR_INT1_PIN PIN5_ID

#define DCMOTOR_INT2_PORT PORTD_ID

#define DCMOTOR_INT2_PIN PIN6_ID

#define DCMOTOR_ENABLE1_PORT PORTB_ID

#define DCMOTOR_ENABLE1_PIN PIN3_ID

#define DcMotor_dutyCylce uint8

/* **************************************  Types Declaration ***************************************************** */


typedef enum
{
	DC_MOTOR_STOP,DC_MOTOR_CW,DC_MOTOR_ACW
}DcMotor_State;


 /* ************************************** Prototypes ***************************************************** */

void DcMotor_Init(void);

void DcMotor_Rotate( DcMotor_State state , DcMotor_dutyCylce duty_cycle);


#endif /* DCMOTOR_H_ */
