/*
 * pwm.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Mina
 */
#include"pwm.h"
#include <avr/io.h>
#include "dcmotor.h"
#include"gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed by updating the value
 * in The Compare Register
 */

void PWM_Timer0_start(uint8 duty_cycle_percentage)
{
	uint8 duty_cycle; // to make it easy to use
	duty_cycle=(uint8)((((float32)duty_cycle_percentage)/100)*255);
	TCNT0 = 0; //Set Timer Initial value
	OCR0  = duty_cycle; // Set Compare Value
	GPIO_setupPinDirection(MOTOR_PORT_E1,MOTOR_PIN_E1,PIN_OUTPUT);  //set OC0 as output pin
#ifdef SECOND
	GPIO_setupPinDirection(MOTOR_PORT_E2,MOTOR_PIN_E2,PIN_OUTPUT);
#endif
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
