/*
 * Ultrasonic.h
 *
 *  Created on: Mar 4, 2024
 *      Author: mod_n
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#include"std_types.h"

/******************************  Definitions  *********************************************** */

#define Ultrasonic_TRIGGER_PORT_ID                 PORTB_ID
#define Ultrasonic_TRIGGER_PIN_ID                  PIN5_ID

/*****************************  Functions Prototypes  ***********************************************  */

/*
 * Description :
 * Initialize the Ultra-sonic:
 * 1. Setup the Ultra-sonic trigger pin directions by use the GPIO driver.
 * 2. Setup the ICU initialization .
 * 3. Setup the Call back of the ICU .
 */
void Ultrasonic_init(void);

/*
 * Description :
 * Send the required trigger pulse to the ultra-sonic .
 */
void Ultrasonic_Trigger(void);

/*
 * Description :
 * 1.calling trigger function .
 * 2.polling until ICU finished .
 * 3.return the distance in cm .
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description :
 * they are only 2 stages ( rising and falling ) to determine the high time ( pulse time ) .
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
