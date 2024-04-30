/*
 * ICU.h
 *
 *  Created on: Mar 4, 2024
 *      Author: mod_n
 */

#ifndef ICU_H_
#define ICU_H_


#include"std_types.h"

/******************************  Definitions  *********************************************** */

#define ICU_PORT_ID		PORTD_ID

#define ICU_PIN_ID		PIN6_ID


/******************************  Types Declaration   *********************************************** */

typedef enum
{
	FALLING_EDGE,RISING_EDGE
}ICU_EdgeType;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,
}ICU_ClockSelect;

typedef struct
{
	ICU_EdgeType		Edge;
	ICU_ClockSelect 	Clock;
}ICU_Configurations;


/*****************************  Functions Prototypes  ***********************************************  */

/*
 * Description :
 * Initialize the ICU:
 * 1. Setup the ICU pin directions by use the GPIO driver.
 * 2. Setup the ICU edge falling or rising.
 * 3. Setup the ICU clock precaler.
 * 4. Setup the ICU initial values.
 * 5. Enable the ICU mask.
 */
void ICU_Init( const ICU_Configurations * Ptr_Configs );

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/*
 * Description: Function to clear the timer register value.
 */
void ICU_ClearTimerValue(void);

/*
 * Description: Function to read the ICU register value.
 */
uint16 ICU_ReadValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void);

#endif /* ICU_H_ */
