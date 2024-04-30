/*
 * TIMER1.c
 *
 *  Created on: Mar 23, 2024
 *      Author: mod_n
 */

#include"TIMER1.h"
#include<avr/io.h>
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/************************Interrupt Service Routines*****************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/************************ Functions Definitions *****************/

/*
 * Description :
 * Function for initiating Timer1 by:
 * 1. Setup the Timer1 mode .
 * 2. Setup the Timer1 pre-scaler .
 * 3. Setup the Timer1 initial value .
 * 4. enable the interrupt module .
 * 5. Setup the Timer1 compare value ( in compare mode only ) .
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
	/* for  non-PWM mode */

	TCCR1B = ( ( Config_Ptr->mode & 0x0C )<<1) | (Config_Ptr->prescaler);
	/* 1. masking with 0x0C ( 0000 1100 ) to capture just bit 2 and 3 then
	 * shift left by 1 to put them in WGM12 & WGM13 mode bits .
	 *
	 * 2. then set the pre-scaler .
	 */

	TCNT1 = Config_Ptr->initial_value;

	if( Config_Ptr->mode == TIMER1_CTC_MODE )
	{
		OCR1A = Config_Ptr->compare_value;
		TIMSK |= (1<<OCIE1A);
	}
	/* ( if compare mode ON )
	 * 1. Setup the compare value by initiate the ( OCR1A register ).
	 * 2. Compare interrupt module enabled .
	 */

	else
	{
		TIMSK |= (1<<TOIE1);
	}
	/* ( if normal mode ON )
	 *  normal interrupt module enabled .
	 */
}


/*
 * Description :
 * Function for de-initiating Timer1 by :
 * 1. Clear all Timer1 registers .
 * 2. disable the interrupt module .
 * 3. Reset the global pointer value .
 */
void Timer1_deInit(void)
{

	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	/* Clear all Timer1 registers . */

	TIMSK &= ~(1<<TOIE1) & ~(1<<OCIE1A);
	/* Compare and normal interrupt modules disabled . */

	g_callBackPtr = NULL_PTR;
	/* Reset the global pointer value . */
}


void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
	/* Save the address of the Call back function in a global variable */
}
