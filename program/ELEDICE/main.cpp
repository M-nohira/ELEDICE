/*
* ELEDICE.cpp
*
* Created: 2019/04/14 0:20:46
* Author : N_M
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "../../../../../toolchain/avr8/avr8-gnu-toolchain/avr/include/avr/iotnx5.h"

#define F_CPU 16000000UL

#define DICE1 0b001000
#define DICE2 0b000001
#define DICE3 0b011000
#define DICE4 0b010001
#define DICE5 0b011001
#define DICE6 0b010011
#define DICEALL 0b011011
#define DICEOFF 0b000000

int Display_Dice(int num);

ISR(ADC_vect)
{
	int adc = ADC;
	if(adc < 256) return;
	
	for(int cnt = 0;cnt < 20;cnt++)
	{
		int ran = -1;
		int r = rand() % 6;
		if(ran == r)
		{
			r= (r + 3) % 6;
		}
		ran = r;
		//Display_Dice(7);	//DICE OFF
		_delay_ms(50);
		Display_Dice(ran);
		_delay_ms(150);
	}
	_delay_ms(3500);
	Display_Dice(7);
}


int main(void)
{
	/* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	_delay_ms(2000);
	DDRB = 0b111011;
	PORTB = 0x00;
	ADCSRA=
	(1 << ADEN)|	//ADC Enable
	(1 << ADSC)|	//ADC start
	(1 << ADATE)|	//ADC auto Trigger Enable
	(1 << ADIF)|	//ADC Interrupt Flag
	(1 << ADIE)|	//ADC Interrupt
	(0b000 <<ADPS0);	//ADC Clock
	ADCSRB = (0b000 << ADTS0);	//ADC sampling in Continuity
	ADMUX =
	(0b00 << REFS0)|	//内部VCC電源参照
	(0 << ADLAR)|	//右詰め
	(0b0001 << MUX0);	//ADC1を参照
	DIDR0 = (1 << ADC1D);	//Enable ADC on ADC1
	
	sei();
	set_sleep_mode(SLEEP_MODE_IDLE);
	while (1)
	{
		sleep_mode();
	}
}


int Display_Dice(int num)
{
	switch(num)
	{
		case 0: PORTB = DICE1; break;
		case 1: PORTB = DICE2; break;
		case 2: PORTB = DICE3; break;
		case 3: PORTB = DICE4; break;
		case 4: PORTB = DICE5; break;
		case 5: PORTB = DICE6; break;
		default: PORTB = DICEOFF; break;
	}
	return 0;
}
