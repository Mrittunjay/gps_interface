#include <lpc214x.h>
#include "lcd_driv.h"

void comd(unsigned char a) {
		IO0CLR|=(LCD|RS|RW|E);
		IO0CLR|=RS;
		IO0SET|=a<<16;
		IO0SET|=E;
		delay_fv(150,150);
		IO0CLR|=E;
}

void data(unsigned int b) {
		IO0CLR|=(LCD|RS|RW|E);
		IO0SET|=RS;
		IO0SET|=b<<16;
		IO0SET|=E;
		delay_fv(150,150);
		IO0CLR|=E;
}

//The Dealy function	 
void delay_fv(unsigned int x,int y) {
		unsigned int i,j;
		for(i=0;i<x;i++)
		for(j=0;j<y;j++);
}

void lcd_clean(void) {
		comd(0x01);
}

void lcd_2nd_line(void) {
		comd(0xC0);
}

void lcd_1st_line(void) {
		comd(0x80);
}

void lcd_init(void) {
	//LCD initilization commands
		PINSEL0 |= 0x00000000;
		IO0DIR |= 0x00FFF000;
		comd(0x80);
		comd(0x38);
		comd(0x0e);
		comd(0x06);
}

void send_string_to_lcd(char *str) {
		int i;
		while(str[i]!='\0') {
				if(i==16)
						comd(0xC0);
				data(str[i]);
				delay_fv(5, 5);
				i++;
		}
}
