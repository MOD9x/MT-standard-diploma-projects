/*
 * BUZZER.h
 *
 *  Created on: Mar 25, 2024
 *      Author: mod_n
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"


/******************************  Definitions  ************************************************************************/
#define BUZZER_PORT_ID PORTC_ID

#define DCMOTOR_PIN_ID PIN7_ID

/******************************  Types Declaration   *****************************************************************/


/*****************************  Functions Prototypes  ****************************************************************/

/*
 * Description : function for initiate the Buzzer by :
 * 1. Setup pin Direction .
 * 2. Turn off the buzzer .
 */
void Buzzer_init(void);

/*
 * Description : function for turn on the buzzer .
 */
void Buzzer_on(void);

/*
 * Description : function for turn off the buzzer .
 */
void Buzzer_off(void);



#endif /* BUZZER_H_ */
