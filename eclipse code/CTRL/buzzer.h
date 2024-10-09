/*
 * buzzer.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Mina
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define Buzzer_PORT_ID  PORTD_ID
#define Buzzer_PIN_ID	PIN4_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the buzzer device by:
 * 1. Initialization .
 * 2. On .
 * 3. OFF.
 */

void buzzer_init(void);

void buzzer_ON(void);

void buzzer_OFF(void);


#endif /* BUZZER_H_ */
