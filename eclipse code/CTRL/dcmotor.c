/*
 * dc-motor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Mina
 */
#include "dcmotor.h"
#include "pwm.h"
#include"gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void DcMotor_init(void){
	GPIO_setupPinDirection(MOTOR_PORT_IN1,MOTOR_PIN_IN1,PIN_OUTPUT);   // make motor pins as output
	GPIO_setupPinDirection(MOTOR_PORT_IN2,MOTOR_PIN_IN2,PIN_OUTPUT);

	GPIO_writePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1,LOGIC_LOW);      //Initially stop
	GPIO_writePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2,LOGIC_LOW);

#ifdef SECOND
	GPIO_setupPinDirection(MOTOR_PORT_IN3,MOTOR_PIN_IN3,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_IN3,MOTOR_PIN_IN3,PIN_OUTPUT);

	GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_LOW);
#endif
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){ //case to run the motor in diffrent direction
	PWM_Timer0_start(speed);  //to change the speed of motors
	switch(state)
	{
	case CW:
		GPIO_writePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2,LOGIC_LOW);

#ifdef SECOND
		GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_LOW);
#endif

		break;
	case A_CW:
		GPIO_writePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2,LOGIC_HIGH);

#ifdef SECOND
		GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_HIGH);
#endif

		break;
	case STOP:

		GPIO_writePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2,LOGIC_LOW);

#ifdef SECOND
		GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOGIC_LOW);
#endif
		break;
	}

}


