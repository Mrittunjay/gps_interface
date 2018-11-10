#include <lpc21xx.h>
#include <stdint.h>
#include "uart_driv.h"

/**********************FOR UART1*****************************************************/
void Uart1Init (void)  {               	   
    PINSEL0 |= 0x00050000;                                
    U1LCR = 0x83;										           
		
	U1DLM = 0x00;
	U1DLL = 0x61;       
	U1FDR = 0x0000007C; /* MULVAL bits -> 7:4) is set to 15 and DIVADDVAL (bits -> 3:0) is set to 0*/

	U1LCR = 0x03; 		 
}
				
void Uart1PutCh (unsigned char ch) {                		
   	U1THR = ch;
	  while (!(U1LSR & 0x20));
}

void  Uart1PutS(unsigned char *str) { 
   while(*str)  {  
      Uart1PutCh(*str++);	    
   }
}
unsigned char Uart1GetCh (void)	{	          
  while (!(U1LSR & 0x01));
  return (U1RBR);
}
/**************************************************************************************/

