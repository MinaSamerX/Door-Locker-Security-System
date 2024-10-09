/*
 * timer.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Mina
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include"std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLK_SOURCE,N_1,N_8,N_64,N_256,N_1024
}Timer1_Prescaler;

typedef enum
{
	NORMAL,COMPARE
}Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * A function to initialize the timer
 */
void TIMER1_init(const Timer1_ConfigType* config_ptr);

/*
 * Description :
 * A function to disable the timer
 */
void TIMER1_deInit(void);

/*
 * Description : -
 * A function to set callback function
 */
void TIMER1_setCallBack(void ( *a_ptr ) ( void ));

#endif /* TIMER1_H_ */
