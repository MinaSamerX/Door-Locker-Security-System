/*
 * timer.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Mina
 */
#include"timer1.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void TIMER1_init(const Timer1_ConfigType * Config_Ptr)
{
	/*
	 * For TCCR1A register : -
	 * non-pwm mode so FOC1A and FOC2A = 1
	 * in case of compare and normal mode , WGM11 & WGM10 & WGM13 = 0
	 * but only WGM12 = 1 in case of compare and equal to 0 in case of normal mode
	 */
	TCCR1A = ( 1 << FOC1A ) | ( 1 << FOC1B );
	/*
	 * For TCCR1B register : -
	 * WGM12 = 1 -> Compare mode or 0 -> Normal mode
	 * CS12 : CS10 = prescaler value
	 */
	TCCR1B = ( Config_Ptr ->prescaler ) | ( ( Config_Ptr ->mode ) << WGM12 );

	TCNT1 =Config_Ptr->initial_value;		/* Set timer1 initial value */

	if(Config_Ptr->mode==NORMAL)
	{
		TCCR1B&=~(1<<WGM12);
		TIMSK|=(1<<TOIE1);//Overflow Interrupt Enable

	}
	else if(Config_Ptr->mode==COMPARE)
	{
		TCCR1B|=(1<<WGM12);
		OCR1A = Config_Ptr->compare_value;    /* Set timer1 compare value */
		TIMSK |= (1 << OCIE1A); //Output Compare A Match Interrupt Enable
	}
}
void TIMER1_deInit(void){
	/* clear all registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK = 0;
	TCNT1 = 0;
	OCR1A = 0;
}

void TIMER1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

