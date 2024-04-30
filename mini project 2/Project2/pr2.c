/*
 * pr2.c
 *
 *  Created on: Feb 3, 2024
 *      Author: mod_n
 */

#include<avr/io.h>

#include<avr/interrupt.h>

#include<stdio.h>

#include<util/delay.h>

#define timer time.timerr // 3shan mksl a8yaroo fel main t7t

union data
{
	unsigned long long timer_reset;
	unsigned char timerr[6];
}time;

unsigned char counter=0;

ISR(INT0_vect)
{
	time.timer_reset = 0 ; // stop watch resetted
}

ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS12) & ~(1<<CS10) ; // stop watch paused
}

ISR(INT2_vect)
{
	TCCR1B |= (1<<CS12) | (1<<CS10) ; // stop watch resumed
}

void TIM1_Init(void)
{
	TCCR1A |= (1<<FOC1A) ; //

	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10) ;

	TCNT1=0;

	OCR1A=977;
}

void INT_Init(void)
{
	DDRD &= ~(1<<PD2) & ~(1<<PD3) ; // configure PD2 and PD3 as I/P pins

	PORTD |=(1<<PD2); // Internal pull up enabled in PD2

	DDRB &= ~(1<<PB2) ; // configure PB2 as I/P pins

	PORTB |=(1<<PB2); // Internal pull up enabled in PB2

	MCUCR |= (1<<ISC01) | (1<<ISC10) | (1<<ISC11); // configure INT0 and INT2 to falling edge and INT1 to rising edge

	GICR  |= (1<<INT0) | (1<<INT1) | (1<<INT2) ; // all EXT INTs masks are enabled (module interrupt)

	SREG |= (1<<7); // I-bit enabled

}

int main()
{
	char i =0;
	INT_Init(); // External interrupts initialization

	TIM1_Init(); // Timer 1 initialization

	time.timer_reset = 0 ;



	DDRC |= 0x0F; // configure PC0 - PC3 as O/P pins

	DDRA |= 0x3F; // configure PA0 - PA5 as O/P pins

	while(1)
	{
		PORTA = (PORTA & 0xC0) | (1<<(5-counter)) ;
		/* setting the first 6 pins only of PORTA
		 * (5-counter) to reverse the displayed 7-segment
		 */

		PORTC = (PORTC & 0xF0) | timer[counter] ;
		/*setting the first 4 pins only of PORTC ANDing with
		 * the element of the array timer based on the counter
		 */

		_delay_us(0);

		/*
		 * timer[0] is the first digit of seconds
		 * timer[1] is the second digit of seconds
		 * timer[2] is the first digit of minutes
		 * timer[3] is the second digit of minutes
		 * timer[4] is the first digit of hours
		 * timer[5] is the second digit of hours
		 */

		if( timer[0] == 10)
		{
			timer[0] =0;
			timer[1]++;
		}

		else if( timer[1] == 6)
				{
					timer[1] =0;
					timer[2]++;
				}

		else if( timer[2] == 10)
						{
							timer[2] =0;
							timer[3]++;
						}

		else if( timer[3] == 6)
						{
							timer[3] =0;
							timer[4]++;
						}
		else if( timer[4] == 10)
						{
							timer[2] =0;
							timer[3]++;
						}

		else if( timer[5] == 10)
						{
							time.timer_reset = 0 ;
						}
		counter++;

		if(counter == 6)
		{
			counter=0;
		}

		if( (TIFR & (1<<OCF1A) ) )
		{
		timer[0]++;
		TIFR |= (1<<OCF1A);
		}

	}
}

