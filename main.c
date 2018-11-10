#include "my_gps_interface.h"
#include <string.h>

int main(void) {
	GGA_Index = 0;
	memset(GGA_String, 0 , 150);
	memset(Latitude_Buffer, 0 , 15);
	memset(Longitude_Buffer, 0 , 15);
	memset(Time_Buffer, 0 , 15);
	memset(Altitude_Buffer, 0 , 8);
	VICVectAddr0 = (unsigned) UART0_Interrupt;	
	VICVectCntl0 = 0x00000026;	
	VICIntEnable = 0x00000040;	
	VICIntSelect = 0x00000000;	
	UART0_init();
	lcd_init();
	
	lcd_clean();
	send_string_to_lcd("STARING");
	delay_fv(4000, 4000);
	lcd_clean();
	lcd_clean();
	send_string_to_lcd("STARING .");
	delay_fv(4000, 4000);
	lcd_clean();
	send_string_to_lcd("STARING	. .");
	delay_fv(4000, 4000);
	lcd_clean();
	send_string_to_lcd("STARING . . .");
	delay_fv(4000, 4000);
	lcd_clean();
	send_string_to_lcd("STARING . . . .");
	delay_fv(4000, 4000);
	lcd_clean();

	while(1) {
		lcd_clean();
		delay_fv(2000, 2000);
		lcd_1st_line();
		delay_ms(1000);
																					
		send_string_to_lcd("UTC Time : ");
		get_Time();																
		send_string_to_lcd(Time_Buffer);												
																		
		lcd_2nd_line();
		send_string_to_lcd("Latitude :");
		get_Latitude(GGA_Comma_Pointers[0]);
		send_string_to_lcd(Latitude_Buffer);
															
		lcd_clean();
		lcd_1st_line();
		send_string_to_lcd("Longitude : ");
		get_Longitude(GGA_Comma_Pointers[2]);
		send_string_to_lcd(Longitude_Buffer);
																															
		lcd_2nd_line();																										
		send_string_to_lcd("Altitude : ");
		get_Altitude(GGA_Comma_Pointers[7]);
		send_string_to_lcd(Altitude_Buffer);
		delay_fv(4000, 4000);
																																	
		GGA_Index = 0;
		memset(GGA_String, 0 , 150);
		memset(Latitude_Buffer, 0 , 15);
		memset(Longitude_Buffer, 0 , 15);
		memset(Time_Buffer, 0 , 15);
		memset(Altitude_Buffer, 0 , 8);
	}
}
