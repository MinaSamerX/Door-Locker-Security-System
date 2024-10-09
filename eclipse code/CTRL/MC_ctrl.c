/*
 * MC_ctrl.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Mina
 */
/*******************************************************************************
 *                           Included libraries                                *
 *******************************************************************************/
#include"MC_ctrl.h"
#include"buzzer.h"
#include"uart.h"
#include"twi.h"
#include"dcmotor.h"
#include "timer1.h"
#include "util/delay.h"
#include"external_eeprom.h"
#include"avr/io.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 counter=0,error;
uint16 g_tick = 0;
static Timer1_ConfigType Timer_Config = {0,7813,N_1024,COMPARE};
/*******************************************************************************
 *                       FUNCTION FOR ISR                                      *
 *******************************************************************************/
void Calculate_time(void)
{
	g_tick ++;
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void START_init(void){ //devices initialization
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_ConfigType UART_Configurations = {DISABLED,ONE_BIT,EIGHT_BIT,9600}; //uart configurations
	TWI_ConfigType TWI_Configurations = {0b00000010,0x02,pre_1};       //I2C config


	SREG|=(1<<7);      //allow interrupt register bit

	buzzer_init();   // buzzer initialization
	DcMotor_init();  //motor initialization
	TWI_init(&TWI_Configurations);  // i2c initialization
	UART_init(&UART_Configurations);  // uart initialization
	TIMER1_setCallBack(Calculate_time);  // timer1 isr functions

	while(UART_recieveByte()!= M1_READY);  //waiting msu1 to be ready
	UART_sendByte(M2_READY); //tell mcu1 that mcu2 is ready it

}
void receive_pass(void){   //receiving pass and save it
	uint16 pass[15];
	uint8 i=0;
	while(UART_recieveByte()!= SAVE);
	UART_sendByte(M2_READY);
	counter=UART_recieveByte();
	while(i<counter){
		UART_sendByte(M2_READY);
		pass[i] =UART_recieveByte();
		EEPROM_writeByte((0x0300+i),pass[i]);
		_delay_ms(70);
		i++;
	}
	UART_sendByte(END_SAVING);
}



void check_pass(void){    //checking pass from memory
	uint16 pass_saved[15];
	uint16 temp_pass[15];
	uint8 i=0;

	while(UART_recieveByte()!= CHECK_PASS);
	while(UART_recieveByte()!= SAVE);
	UART_sendByte(M2_READY);
	counter=UART_recieveByte();
	while(i<counter){

		UART_sendByte(M2_READY);
		temp_pass[i] =UART_recieveByte();
		_delay_ms(200);
		i++;
	}
	UART_sendByte(END_SAVING);
	i=0;
	while(i<counter){
		EEPROM_readByte((0x0300+i), pass_saved);

		if(temp_pass[i] != pass_saved[i])
		{
			UART_sendByte(Error_pass);
		}
		else
		{

			UART_sendByte(CONTINUE_PASS);
		}

		i++;
	}
	error = UART_recieveByte();
	if(error < 3)
	{
		check_pass();
	}
	else if(error == 3)
	{
		TIMER1_deInit();
		TIMER1_init(&Timer_Config);
		g_tick =0;

		while (g_tick != 60)
		{
			buzzer_ON();
		}
	}
}
void open_door(void){  //controling door
	while(UART_recieveByte()!= UNLOCK_DOOR);
	TIMER1_deInit();
	TIMER1_init(&Timer_Config);
	g_tick =0;
	while(g_tick != 15)
	{
		DcMotor_Rotate(CW,100);
	}
	g_tick =0;
	while(g_tick != 3)
	{
		DcMotor_Rotate(STOP,0);
	}
	g_tick =0;
	while(g_tick != 15)
	{
		DcMotor_Rotate(A_CW,100);
	}

	DcMotor_Rotate(STOP,0);
}
void main_options(void){   //main options set menu
	check_pass();
	if(UART_recieveByte() == 0)
	{
		if(UART_recieveByte() == '+')
		{

			open_door();
		}
		else
		{
			receive_pass();

		}
	}

	else
	{
		buzzer_OFF();
	}

}


