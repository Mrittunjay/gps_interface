#include <lpc214x.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uart_driv.h"
#include "lcd_driv.h"
#include "my_gps_interface.h"

void delay_ms(uint16_t j) {
    uint16_t x,i;
	for(i=0;i<j;i++) {
    	for(x=0; x<6000; x++); 
	}
}

__irq void UART0_Interrupt(void) {
	int iir_value;
	char received_char;
	iir_value = U0IIR;
		received_char = U0RBR;
			if( received_char == '$' ) {
				GGA_Index = 0;
				CommaCounter = 0;
				IsItGGAString = false;
			}
			else if( IsItGGAString == true ) {
				if ( received_char == ',' )	{
					GGA_Comma_Pointers[CommaCounter++] = GGA_Index;
				}
				GGA_String[GGA_Index++] = received_char;
			}
			else if( ( GGA[0] == 'G' ) && ( GGA[1] == 'G' ) && ( GGA[2] == 'A' ) ) {
				IsItGGAString = true;
				GGA[0] = GGA[1] = GGA[2] = 0;
			}
			else {
				GGA[0] = GGA[1];
				GGA[1] = GGA[2];
				GGA[2] = received_char;
			}
	VICVectAddr = 0x00;
}

void get_Time(void) {
	U0IER = 0x00000000;
	
	uint8_t time_index=0;
	uint8_t index;
	uint16_t hour, min, sec;
	uint32_t Time_value;

	for(index = 0; GGA_String[index]!=','; index++) {		
		Time_Buffer[time_index] = GGA_String[index];
		time_index++;
	}	
	Time_value = atol(Time_Buffer);               
	hour = (Time_value / 10000);                  
	min = (Time_value % 10000) / 100;             
	sec = (Time_value % 10000) % 100;           

	sprintf(Time_Buffer, "%d:%d:%d", hour,min,sec);
	
	U0IER = 0x00000001; 
}


void get_Latitude(uint16_t Latitude_Pointer) {
	U0IER = 0x00000000;
	
	uint8_t lat_index = 0;
	uint8_t index = (Latitude_Pointer+1);
	
	for(;GGA_String[index]!=',';index++) {
		Latitude_Buffer[lat_index]= GGA_String[index];
		lat_index++;
	}
	
	float lat_decimal_value, lat_degrees_value;
	int32_t lat_degrees;
	lat_decimal_value = atof(Latitude_Buffer);       
	
	lat_decimal_value = (lat_decimal_value/100);
	lat_degrees = (int)(lat_decimal_value);
	lat_decimal_value = (lat_decimal_value - lat_degrees)/0.6;	
	lat_degrees_value = (float)(lat_degrees + lat_decimal_value);		
	sprintf(Latitude_Buffer, "%f", lat_degrees_value);
	
	U0IER = 0x00000001; 
}


void get_Longitude(uint16_t Longitude_Pointer) {
	U0IER = 0x00000000; 
	
	uint8_t long_index = 0;
	uint8_t index = (Longitude_Pointer+1);
	
	for(;GGA_String[index]!=',';index++) {
		Longitude_Buffer[long_index]= GGA_String[index];
		long_index++;
	}
	
	float long_decimal_value, long_degrees_value;
	int32_t long_degrees;
	long_decimal_value = atof(Longitude_Buffer);	
	
	long_decimal_value = (long_decimal_value/100);	
	long_degrees = (int)(long_decimal_value);	
	long_decimal_value = (long_decimal_value - long_degrees)/0.6;	
	long_degrees_value = (float)(long_degrees + long_decimal_value);	
	sprintf(Longitude_Buffer, "%f", long_degrees_value);
	
	U0IER = 0x00000001;
}


void get_Altitude(uint16_t Altitude_Pointer) {
	U0IER = 0x00000000;
	
	uint8_t alt_index = 0;
	uint8_t index = (Altitude_Pointer+1);
	
	
	for(;GGA_String[index]!=',';index++) {
		Altitude_Buffer[alt_index]= GGA_String[index];
		alt_index++;
	}
	U0IER = 0x00000001;
}

