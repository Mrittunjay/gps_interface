
#ifndef MY_GPS_INTERFACE_H
#define MY_GPS_INTERFACE_H

char Latitude_Buffer[15],Longitude_Buffer[15],Time_Buffer[15],Altitude_Buffer[8];
char iir_val[10];
char GGA_String[150];
uint8_t GGA_Comma_Pointers[20];
char GGA[3];
volatile uint16_t GGA_Index, CommaCounter;
bool IsItGGAString = false;

__irq void UART0_Interrupt(void);

void delay_ms(uint16_t);
void get_Time(void);
void get_Latitude(uint16_t);
void get_Longitude(uint16_t);
void get_Altitude(uint16_t);

#endif
