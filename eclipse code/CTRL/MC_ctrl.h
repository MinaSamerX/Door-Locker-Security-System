/*
 * MC_ctrl.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Mina
 */

#ifndef MC_CTRL_H_
#define MC_CTRL_H_

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
#define HMI_READY           0x10

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the system by:
 * 1. for all devices initialization .
 * 2. receive first pass and save it.
 * 3. for main option set menu.
 */
void START_init(void);
void receive_pass(void);
void main_options(void);

#endif /* MC_CTRL_H_ */
