/*
 * TIMER1.h
 *
 *  Created on: Mar 23, 2024
 *      Author: mod_n
 */

#ifndef TIMER1_H_
#define TIMER1_H_


#include"std_types.h"

/***************************************** Definitions ***************************************************************/

/***************************************** Types declarations ********************************************************/

typedef enum
{
	TIMER1_NO_PRESCALER,TIMER1_1_PRESCALER,TIMER1_8_PRESCALER,TIMER1_64_PRESCALER,TIMER1_256_PRESCALER,TIMER1_1024_PRESCALER
}Timer1_Prescaler;

typedef enum
{
	TIMER1_NORMAL_MODE , TIMER1_CTC_MODE = 4
}Timer1_Mode;

typedef struct
{
	uint16 initial_value;

    uint16 compare_value;

    Timer1_Prescaler prescaler;

    Timer1_Mode mode;

}Timer1_ConfigType;

/***************************************** Functions prototype *******************************************************/


/*
 * Description :
 * Function for initiating Timer1 by:
 * 1. Setup the Timer1 mode .
 * 2. Setup the Timer1 pre-scaler .
 * 3. Setup the Timer1 initial value .
 * 4. enable the interrupt module .
 * 5. Setup the Timer1 compare value ( in compare mode only ) .
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function for de-initiating Timer1 by :
 * 1. Clear all Timer1 registers .
 * 2. disable the interrupt module .
 * 3. Reset the global pointer value .
 */
void Timer1_deInit(void);

/*
 * Description :
 * Function for setup the Timer1 callback pointer .
 */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
