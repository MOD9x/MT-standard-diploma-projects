/*
 * HMI.c
 *
 *  Created on: Mar 24, 2024
 *      Author: mod_n
 */

#include"TIMER1.h"
#include"UART.h"
#include"LCD.h"
#include"KEYPAD.h"
#include<avr/io.h>
#include <util/delay.h>

#define SIZE 5
#define HMI_READY 0xF0
#define CONTROL_READY 0x0F
#define MATCHED_PASSWORDS 0x0A
#define UNMATCHED_PASSWORDS 0x00

uint8 g_ticks=0;

/*
 * Description : function for reading password from user
 * and save that password in a_array passed then prints '*' .
 */
void Read_password( uint8 * a_array ,uint8 a_size , uint8 row , uint8 col)
{
	uint8 read_counter = 0 ;

	_delay_ms(250);
	/* delay for make sure key pressed once */

	/* Looping on the password to save it in the array */
	while( read_counter < a_size )
	{
		a_array[read_counter] = KEYPAD_getPressedKey();

		LCD_displayCharacterRowColumn( row , col+read_counter , ( a_array[read_counter] + 48 ) );
		/* number + 48 = ASKII of the number */

		_delay_ms(250);
		/* delay for make sure key pressed once */

		LCD_displayCharacterRowColumn( row , col+read_counter , '*');
		/* password masking for safety */

		read_counter++;
	}

	while( KEYPAD_getPressedKey() != '=')
	{
		/* polling until enter key '=' be pressed . */
	}
}

/*
 * Description : function for creating password .
 */
uint8 Creat_password(uint8 * a_array ,uint8 a_size)
{
		LCD_clearScreen();

		LCD_displayString("plz enter pass :");

		Read_password( a_array,a_size,1,0 );

		UART_sendByte(HMI_READY);

		UART_sendArray( a_array , a_size);

		/******************** first password reading and sending by UART ************/

		LCD_displayStringRowColumn(0,0,"plz re-enter the");
		LCD_displayStringRowColumn(1,0,"same pass :");

		Read_password( a_array,a_size,1,11);

		UART_sendByte(HMI_READY);

		UART_sendArray( a_array , a_size);

		/******************** second password reading and sending by UART ************/

		if( UART_receiveByte() == MATCHED_PASSWORDS)
		{
			LCD_clearScreen();
			LCD_displayString("password created");
			_delay_ms(1000);
		}

		else
		{
			LCD_clearScreen();
			LCD_displayString("not matched");
			_delay_ms(1000);
			return UNMATCHED_PASSWORDS;
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
uint8 Passward_login(uint8 * a_array ,uint8 a_size)
{
	LCD_clearScreen();

	LCD_displayString("plz enter pass :");

	Read_password( a_array,a_size,1,0 );

	UART_sendByte(HMI_READY);

	UART_sendArray( a_array , a_size);

	/******************** password reading and sending by UART ************/

	if(UART_receiveByte() == MATCHED_PASSWORDS)
	{
	}
	else
	{
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
	uint8 Arr1[SIZE] ,key=0 , counter=0;;
	/*
	 * Array 1 : is the password .
]	 */

	Timer1_ConfigType Timer1_configs = { 0 , 8000 , TIMER1_1024_PRESCALER , TIMER1_CTC_MODE };
	/* timer1 configurations : initial value , compare value , pre-scaler , timer mode */

	UART_ConfigType UART_Configs = {UART_8bits,UART_parityEven,UART_1StopBit,9600};
	/* UART configurations : number of bits , parity bit , stop bit , baud rate . */

	UART_init(&UART_Configs);
	/* UART initialization */

	LCD_init();

	Timer1_init( &Timer1_configs );
	/* Timer 1 initialization */

	Timer1_setCallBack(TIMER_counter);
	/* Timer 1 callback setting which used in timer 1 ISR */

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

		LCD_displayStringRowColumn(0,0,"+ : open door   ");
		LCD_displayStringRowColumn(1,0,"- : change pass ");

		key = KEYPAD_getPressedKey();
		/****************** main options ******************************************/

		UART_sendByte(key);

		if( key != '+' && key !='-' )
		{
			continue;
		}
		/* to make sure key is '-' or '+' only
		 * else program will do nothing .
		 */

		while ( Passward_login(Arr1,SIZE) != MATCHED_PASSWORDS)
		{
			counter--;

			g_ticks=0;

			if( counter == 0 )
			{
				LCD_displayStringRowColumn(0,0,"wrong pass try  ");
				LCD_displayStringRowColumn(1,0,"again in    sec ");

				while( g_ticks != 60)
				{
					LCD_intgerToStringRowColumn(1,9, ( 60 - g_ticks ) );

					if( g_ticks == 51 )
					{
						LCD_displayCharacterRowColumn(1,10,' ');
					}
				}

				break;
				/* to exit from the while loop */
			}
			/* HMI locked after 3 consecutive wrong passwords for 60 seconds using timer . */

			else
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"wrong pass you  ");
				LCD_displayStringRowColumn(1,0,"have   chance   ");
				LCD_intgerToStringRowColumn(1,5, counter );

				while( g_ticks != 3);
				/* delay for 3 sec */
			}
			/* warning message display */

		}
		/* if the function returned ( matched = True = 0x0A ) program will continue
		 * if returned ( unmatched = False = 0 )  program will ask again 2 more times .
		 */

		if( counter == 0 )
		{
			continue;
		}
		/* to go back to main options*/

		if( key == '+' )
		{
			g_ticks=0;

			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"door is opening ");

			while( g_ticks != 15);
			/* delay for 15 sec */

			LCD_displayStringRowColumn(0,8,"opened ");

			while( g_ticks != 18);
			/* delay for 3 sec */

			LCD_displayStringRowColumn(0,8,"closing  ");

			while( g_ticks != 33);
			/* delay for 15 sec */
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

