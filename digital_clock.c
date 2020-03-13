#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <avr/interrupt.h>
#include <stdlib.h>
int s=00;
int h=01;
int m=40;
ISR (TIMER1_OVF_vect)
{
	TIFR=(1<<TOV1);
	TCNT1=57723;
	s++;
}
int main()
{
	char s1[4];
	char s2[4];
	char s3[4];
	DDRA=0xFF;
	DDRB=0xFF;
	TCNT1=57723;
	sei();
	TIMSK|=(1<<TOV1);
	TCCR1B=0x05;
	while (1){
	if (s>59)
	{
		s=00;
		m++;
		if (m>59)
		{
			h++;
			m=00;
		}
		if (h>24)
		h=00;
	}
	lcd_init();
	lcd_print(itoa(h,s1,10));
	lcd_print(":");
	lcd_print(itoa(m,s2,10));
	lcd_print(":");
	lcd_print(itoa(s,s3,10));}
}