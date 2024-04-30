/*
 * ICU.c
 *
 *  Created on: Mar 4, 2024
 *      Author: mod_n
 */

#include"ICU.h"

#include "gpio.h"

#include <avr/interrupt.h>

#include<avr/io.h>

/*****************************  Global Variables  ***********************************************  */


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*****************************  Interrupt Service Routines  ***********************************************  */

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*****************************  Functions   ***********************************************  */


/*
 * Description :
 * Initialize the ICU:
 * 1. Setup the ICU pin directions by use the GPIO driver.
 * 2. Setup the ICU edge falling or rising.
 * 3. Setup the ICU clock precaler.
 * 4. Setup the ICU initial values.
 * 5. Enable the ICU mask.
 */
void ICU_Init( const ICU_Configurations * Ptr_Configs )
{
	GPIO_setupPinDirection(ICU_PORT_ID,ICU_PIN_ID , PIN_INPUT);

	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	/* for non PWM we using normal mode*/

	TCCR1B = (TCCR1B & 0xBF) | (Ptr_Configs->Edge<<ICES1);
	/* clearing bit number 6 then set it with the edge from struct */

	TCCR1B = (TCCR1B & 0xF8) | (Ptr_Configs->Clock);
	/* clearing 1st 3 bits then set them with the clock from struct */

	TCNT1=0; /* timer initial value */

	ICR1=0; /* ICU initial value */

	TIMSK |= (1<<TICIE1); /* ICU interrupt mask enabled */

}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_Edge)
{
	TCCR1B = (TCCR1B & 0xBF) | (a_Edge<<ICES1);
	/* clearing bit number 6 then set it with the edge at the argument*/
}

/*
 * Description: Function to clear the timer register value.
 */
void ICU_ClearTimerValue(void)
{
	TCNT1=0; /* timer initial value */
}

/*
 * Description: Function to read the ICU register value.
 */
uint16 ICU_ReadValue(void)
{
	return ICR1;
}


/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void)
{
	/* Clear All Timer1/ICU Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);

	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}



