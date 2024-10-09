/*
 * main.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Mina
 */

#include "HMI_ctrl.h"

int main(void){

	START_init();   //start initialization of components

	Lock_NewPass();  //// send first pass and save it

	while(TRUE)
	{
		Main_Options();   //for main option set menu
	}
	return FALSE;
}

