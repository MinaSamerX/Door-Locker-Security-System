/*
 * main.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Mina
 */
#include"MC_ctrl.h"

int main(void){

	START_init(); //start initialization of components

	receive_pass();  // receive first pass and save it

	while(1)
	{
		main_options(); //for main option set menu
	}
	return FALSE;
}
