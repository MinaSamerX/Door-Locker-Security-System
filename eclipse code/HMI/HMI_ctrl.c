/*
 * HMI_ctrl.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Mina
 */
/*******************************************************************************
 *                           Included libraries                                *
 *******************************************************************************/
#include"HMI_ctrl.h"
#include"timer1.h"
#include"keypad.h"
#include"lcd.h"
#include "uart.h"
#include <util/delay.h>
#include"avr/io.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 counter=0;
uint16 g_tick = 0;
uint8 counter_error =0;
uint8 return_flag=0;
uint8 send_flag =1;
static Timer1_ConfigType Timer_Config = {0,7813,N_1024,COMPARE};
/*******************************************************************************
 *                       FUNCTION FOR ISR                                      *
 *******************************************************************************/
void Calculate_time(void)
{
	g_tick ++;  //increment every one sec
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void START_init(void){
	UART_ConfigType UART_Configurations = {DISABLED,ONE_BIT,EIGHT_BIT,9600};  //uart config


	SREG|=(1<<7);      //enable interrupt bit

	LCD_init();   //lcd initialization
	UART_init(&UART_Configurations);   // uart initialization
	TIMER1_setCallBack(Calculate_time);  // isr timer 1 function

	UART_sendByte(M1_READY);   //telling mcu2 that mcu1 is ready
	while(UART_recieveByte()!= M2_READY);  //waiting mcu2 to respond that is he his ready
	LCD_displayStringRowColumn(0,5,"Welcome");
	LCD_displayStringRowColumn(1,3,"Ready to go");
	_delay_ms((2*D));
	LCD_clearScreen();
	LCD_displayString("PLZ enter pass:");
}

void send_pass(uint16 *pass){  //sending pass to mcu2
	uint8 i=0;
	UART_sendByte(SAVE);
	while(UART_recieveByte() != M2_READY){}
	UART_sendByte(counter);
	while(i<(counter)){
		while(UART_recieveByte() != M2_READY){}
		UART_sendByte(pass[i]);
		i++;
	}
	while(UART_recieveByte()!= END_SAVING);
}
void enter_pass(uint16 *pass){  //entring pass to system
	counter=0;
	uint8 key=KEYPAD_getPressedKey();
	uint8 i=0;
	LCD_moveCursor(1,0);
	while((key!=' ')){
		pass[i]=KEYPAD_getPressedKey();
		_delay_ms(D);
		key=pass[i];
		if(key == ' '){
			break;
		}
		LCD_displayCharacter('*');
		i++;
		counter++;
		_delay_ms(D);
	}
}

void Lock_NewPass(void){  //add frist pass to the system
	uint16 pass1[15],pass2[15];
	uint8 j=0;
	enter_pass(pass1);


	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"PLZ renter it:");
	_delay_ms(50);

	enter_pass(pass2);

	while(j<(counter)){
		if(pass2[j] == pass1[j]){
			j++;
		}
		else{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,6,"ERROR");
			_delay_ms((4*D));
			LCD_clearScreen();
			LCD_displayString("PLZ enter pass:");
			Lock_NewPass();
			break;
		}

	}
	if (send_flag ==1){
		send_pass(pass1);
		LCD_clearScreen();
		LCD_displayString("THANKS pass has");
		LCD_displayStringRowColumn(1,0,"been set.");
		_delay_ms((2*D));
		LCD_displayStringRowColumn(0,0,"+ : open door");
		LCD_displayStringRowColumn(1,0,"- : change pass");
		_delay_ms(D/2);
		send_flag=0;
	}
}

void check_pass(void){  //checking pass
	uint16 pass[15];
	uint8 error_pass=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Enter pass:");
	enter_pass(pass);
	UART_sendByte(CHECK_PASS);
	send_pass(pass);
	if(UART_recieveByte() == Error_pass)
	{
		error_pass ++;
	}

	if(error_pass != 0)
	{
		counter_error ++;
		UART_sendByte(counter_error);

		if(counter_error < 3)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"INCORRECT PASS");
			_delay_ms(2*D);
			check_pass();
		}
		else
		{
			LCD_clearScreen();

			TIMER1_deInit();
			TIMER1_init(&Timer_Config);
			g_tick =0;
			while (g_tick != 60)
			{
				LCD_displayStringRowColumn(0,0,"Wait 60 Seconds");
				LCD_displayStringRowColumn(1,5,"Thief");
			}

			counter_error = 0;
			return_flag =1;
		}
	}
	else
	{
		UART_sendByte(4);
		counter_error = 0;
	}

}


void Open_Door(void){  //open door system
	UART_sendByte(UNLOCK_DOOR);

	LCD_clearScreen();
	TIMER1_deInit();
	TIMER1_init(&Timer_Config);
	g_tick =0;
	while(g_tick != 15)
	{
		LCD_displayStringRowColumn(0,0,"Opening Door..");
	}

	LCD_clearScreen();
	g_tick =0;
	while(g_tick != 3)
	{
		LCD_displayStringRowColumn(0,0,"Door Opened");
	}

	LCD_clearScreen();
	g_tick =0;
	while(g_tick!= 15)
	{
		LCD_displayStringRowColumn(0,0,"Closing Door..");
	}
}

void Main_Options(void){  //main option set menu
	LCD_displayStringRowColumn(0,0,"+ : open door");
	LCD_displayStringRowColumn(1,0,"- : change pass");
	uint8 key;
	while((key != '+') || (key != '-')){
		key=KEYPAD_getPressedKey();
		if((key == '+') || (key == '-')){
			break;
		}
	}
	_delay_ms(D);
	check_pass();
	UART_sendByte(return_flag);
	UART_sendByte(key);
	if(return_flag == 0)
	{
		if(key== '+'){
			Open_Door();
		}
		else if (key== '-'){
			LCD_clearScreen();
			LCD_displayString("Enter new pass:");
			send_flag=1;
			Lock_NewPass();
		}
	}
	else
	{
		return_flag=0;
	}

	LCD_clearScreen();
}



