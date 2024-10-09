/*
 * HMI_ctrl.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Mina
 */

#ifndef HMI_CTRL_H_
#define HMI_CTRL_H_

#include"std_types.h"

/*******************************************************************************
 *                                  Definitions                                *
 *******************************************************************************/

#define M1_READY 			0x10
#define M2_READY 			0x20
#define Error_pass 			0x00
#define SAVE 				0x02
#define END_SAVING 			0x03
#define CHECK_PASS 			0x04
#define CONTINUE_PASS 		0x05
#define UNLOCK_DOOR 		0x06
#define INITIALIZED_FLAG 	0x01

#define D 250


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the  system by:
 * 1. for all devices initialization .
 * 2. send first pass and save it.
 * 3. for main option set menu.
 */
void START_init(void);
void Lock_NewPass(void);
void Main_Options(void);

#endif /* HMI_CTRL_H_ */
