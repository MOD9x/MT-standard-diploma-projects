/*
 * MiniProject3.c
 *
 *  Created on: Feb 22, 2024
 *      Author: mod_n
 */

#include "gpio.h"
#include "lcd.h"
#include "DcMotor.h"
#include"PWM.h"
#include "adc.h"
#include "LM35.h"


int main()
{
	 uint8 Temperature=0 ;

	 ADC_ConfigType ConfigType ={InternalVref_ADC,ADC_F8};

	 DcMotor_Init(); /* initialize DC Motor driver */

	 LCD_init(); /* initialize LCD driver */

	 ADC_init(&ConfigType); /* initialize ADC driver */


	  LCD_displayStringRowColumn( 0 , 4 ,"FAN is OFF");

	  LCD_displayStringRowColumn( 1 , 4 ,"Temp =    C");

	  LCD_intgerToStringRowColumn(1,11,Temperature);


	 while(1)
	 {
		 Temperature = LM35_GetTemperature();

		 if( Temperature<30 )
		 {
			 DcMotor_Rotate( DC_MOTOR_STOP , 0 );
			 LCD_displayStringRowColumn( 0 , 4 ,"FAN is OFF");
			 LCD_intgerToStringRowColumn(1,11,Temperature);

		 	 if(Temperature==9)
		 	 {
		 		 LCD_displayCharacterRowColumn(1,12,' ');
		 	 }

		 }

		 else if( Temperature >= 30 && Temperature < 60)
		  {
		 	 DcMotor_Rotate( DC_MOTOR_CW , 25 );
		 	 LCD_displayStringRowColumn( 0 , 4 ,"FAN is ON ");
		 	 LCD_intgerToStringRowColumn(1,11,Temperature);
		  }

		 else if( Temperature >= 60 && Temperature < 90)
		  {
		 	 DcMotor_Rotate( DC_MOTOR_CW , 50 );
		 	 LCD_displayStringRowColumn( 0 , 4 ,"FAN is ON ");
		 	 LCD_intgerToStringRowColumn(1,11,Temperature);
		  }

		 else if( Temperature >= 90 && Temperature < 120)
		  {
		 	 DcMotor_Rotate( DC_MOTOR_CW , 75 );
		 	 LCD_displayStringRowColumn( 0 , 4 ,"FAN is ON ");
		 	 LCD_intgerToStringRowColumn(1,11,Temperature);

		 	 if(Temperature==99)
		 	 {
		 		LCD_displayCharacterRowColumn(1,13,' ');
		 	 }
		  }

		 else if( Temperature >= 120 )
		  {
		 	 DcMotor_Rotate( DC_MOTOR_CW , 100 );
		 	 LCD_displayStringRowColumn( 0 , 4 ,"FAN is ON ");
		 	 LCD_intgerToStringRowColumn(1,11,Temperature);
		  }

	 }
}
