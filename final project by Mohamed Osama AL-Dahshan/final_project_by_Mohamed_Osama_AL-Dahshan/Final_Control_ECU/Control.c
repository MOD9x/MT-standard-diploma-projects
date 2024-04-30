/*
 * Control.c
 *
 *  Created on: Mar 24, 2024
 *      Author: mod_n
 */

#include"TIMER1.h"
#include"UART.h"
#include"EEPROM.h"
#include"I2C.h"
#include"DcMotor.h"
#include"BUZZER.h"
#include<avr/io.h>
#include <util/delay.h>

#define SIZE 5
#define HMI_READY 0xF0
#define CONTROL_READY 0x0F
#define MATCHED_PASSWORDS 0x0A
#define UNMATCHED_PASSWORDS 0x00

uint16 g_ticks=0;

/*
 * Description : function for passwords match checking .
 */
uint8 Passwords_check(uint8 * a_array  ,uint8 a_size )
{
	uint8 a_array2[a_size],counter = 0 ;
	/* a_array2 : is the second password from EEPROM . */

	EEPROM_readArray(0x00 , a_array2 , a_size);

	/* Looping on the password compare each element from EEPROM to received password */
	while( counter < a_size )
	{
		if( a_array[counter] == a_array2[counter] )
		{

		}

		else
		{
			return UNMATCHED_PASSWORDS ;
		}
		/* if passwords are matched function will return MATCHED_PASSWORDS */
		counter++;
	}

	return MATCHED_PASSWORDS;
}

/*
 * Description : function for creating new password .
 */
uint8 Creat_password( uint8 * a_array1 ,uint8 a_size )
{
		while( UART_receiveByte() != HMI_READY);

		UART_receiveArray( a_array1 , SIZE);

		EEPROM_writeArray(0x00 , a_array1 , SIZE);

		/******************** first password received by UART and saved in EEPROM ************/

		while( UART_receiveByte() != HMI_READY);

		UART_receiveArray( a_array1 , SIZE);

		/******************** second password received by UART ************/

		if(Passwords_check(a_array1 ,a_size ) )
		{
			UART_sendByte(MATCHED_PASSWORDS);
		}
		else
		{
			UART_sendByte(UNMATCHED_PASSWORDS);
			return UNMATCHED_PASSWORDS ;
		}
		/* if the function returned ( matched = True = 0x0A ) program will reply matched
		 * if returned ( unmatched = False = 0 )  program will reply unmatched .
		 */
		return MATCHED_PASSWORDS;

		/******************** passwords checking  ************/
}

/*
 * Description : function for checking the password received by UART .
 */
uint8 Password_login(uint8 * a_array1 ,uint8 a_size )
{
			while( UART_receiveByte() != HMI_READY);

			UART_receiveArray( a_array1 , SIZE);

			/********************  password received by UART ************/

			if(Passwords_check(a_array1 ,a_size ) )
			{
				UART_sendByte(MATCHED_PASSWORDS);
			}
			else
			{
				UART_sendByte(UNMATCHED_PASSWORDS);
				return UNMATCHED_PASSWORDS ;
			}
			/* if the function returned ( matched = True = 0x0A ) program will reply matched
			 * if returned ( unmatched = False = 0 )  program will reply unmatched .
			 */
			return MATCHED_PASSWORDS;

			/******************** passwords checking  ************/

}

void TIMER_counter(void)
{
	g_ticks++;
}

int main()
{
	uint8 Arr1[SIZE] , key = 0 , counter =0 ;
;
	/*
	 * Array 1 : is the first password .
	 */

	Timer1_ConfigType Timer1_configs = { 0 , 8000 , TIMER1_1024_PRESCALER , TIMER1_CTC_MODE };
	/* timer1 configurations : initial value , compare value , prescaler , timer mode */

	TWI_ConfigType TWI_Configs = { 0x10 , 2 };

	UART_ConfigType UART_Configs = {UART_8bits,UART_parityEven,UART_1StopBit,9600};
	/* UART configurations : number of bits , parity bit , stop bit , baud rate . */

	UART_init(&UART_Configs);
	/* UART initialization */

	TWI_init( &TWI_Configs );
	/* TWI initialization */

	DcMotor_Init();
	/* DC motor initialization */

	Buzzer_init();
	/* Buzzer initialization */

	Timer1_init( &Timer1_configs );
	/* Timer 1 initialization */

	Timer1_setCallBack(TIMER_counter);
	/* Timer 1 callback setting which used in timer 1 ISR */

	_delay_ms(10);
	/* Delay for EEPROM */

	SREG |= (1<<7);
	/*  I-bit enabled */

	while(  Creat_password( Arr1 ,SIZE ) != MATCHED_PASSWORDS );
	/* polling if the function returned ( matched = True = 0x0A ) program will continue
	 * if returned ( unmatched = False = 0 )  program will ask again .
	 */


	while(1)
	{
		counter = 3;
		/* number of chance to lock the system */

		key = UART_receiveByte() ;
		/****************** main options ******************************************/

		if( key != '+' && key !='-' )
		{
			continue;
		}
		/* to make sure key is '-' or '+' only
		 * else program will do nothing .
		 */

		while ( Password_login(Arr1,SIZE) != MATCHED_PASSWORDS)
		{
			counter--;

			if( counter == 0 )
			{
				g_ticks=0;

				while( g_ticks <= 60)
				{
					if( g_ticks & 1 )
					{
						Buzzer_on();
					}

					else
					{
						Buzzer_off();
					}
					/* toggle the Buzzer and led every one second .
					 * XXXX XXX1 & 1 = TRUE : if odd second buzzer ON .
					 * XXXX XXX0 & 1 = FALSE: if even second buzzer OFF.
					 */
				}
				/* alarm system ON after 3 consecutive wrong passwords for 60 seconds */

				Buzzer_off();
				/* to make sure buzzer is off */

				break;
				/* to exit from the while loop */
			}
		}
		/* if the Password_login function returned ( matched = True = 0x0A ) program will continue
		 * if returned ( unmatched = False = 0 )  program will ask again 2 more times  .
		 */

		if( counter == 0 )
		{
			continue;
		}
		/* to go back to main options*/

		if( key == '+' )
			{
				g_ticks=0;

				DcMotor_Rotate( DC_MOTOR_CW ,100);
				while( g_ticks != 15);
				/* motor running clockwise for 15 sec */

				DcMotor_Rotate( DC_MOTOR_STOP ,0);
				while( g_ticks != 18);
				/* motor stopping for 3 sec */

				DcMotor_Rotate( DC_MOTOR_ACW ,100);
				while( g_ticks != 33);
				/* motor running anti-clockwise for 15 sec */

				DcMotor_Rotate( DC_MOTOR_STOP ,0);
			}

		else
		{
			while(  Creat_password( Arr1 ,SIZE ) != MATCHED_PASSWORDS );
			/* if the function returned ( matched = True = 0x0A ) program will continue
			 * if returned ( unmatched = False = 0 )  program will ask again .
			 */
		}
	}
}



