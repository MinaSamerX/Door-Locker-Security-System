/*
 * buzzer.c
 *
 *  Created on: Oct 27, 2023
 *      Author: Mina
 */

#include "gpio.h"
#include "buzzer.h"

#include <util/delay.h>


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void buzzer_init(void)
{
	GPIO_setupPinDirection(Buzzer_PORT_ID, Buzzer_PIN_ID, PIN_OUTPUT);  // make pin as output
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID,LOGIC_LOW); //make buzzer off at frist
}

void buzzer_ON(void)
{
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID, LOGIC_HIGH);   //buzzer on
}

void buzzer_OFF(void)
{
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID,LOGIC_LOW);   //buzzer off
}

