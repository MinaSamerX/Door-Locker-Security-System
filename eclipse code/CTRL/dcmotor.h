/*
 * dc-motor.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Mina
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	CW,A_CW,STOP
}DcMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_MOTORS 1

#if((NUM_MOTORS <1) ||(NUM_MOTORS > 2))
#error "Number of motors should be equal to 1 or 2"
#endif

#define FIRST_PORT      //in case using second port only change definitions
#if(NUM_MOTORS == 2)
#define SECOND_PORT
#endif

#ifdef FIRST_PORT
#define MOTOR_PORT_IN1 PORTD_ID
#define MOTOR_PIN_IN1 PIN2_ID

#define MOTOR_PORT_IN2 PORTD_ID
#define MOTOR_PIN_IN2 PIN3_ID

#define MOTOR_PORT_E1 PORTB_ID
#define MOTOR_PIN_E1 PIN3_ID
#endif

#ifdef SECOND_PORT
#define MOTOR_PORT_IN4 PORTA_ID
#define MOTOR_PIN_IN4 PIN0_ID

#define MOTOR_PORT_IN4 PORTA_ID
#define MOTOR_PIN_IN4 PIN1_ID

#define MOTOR_PORT_E2 PORTB_ID
#define MOTOR_PIN_E2 PIN3_ID
#endif

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void DcMotor_init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DCMOTOR_H_ */
