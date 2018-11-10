#ifndef SERIAL_H_
#define SERIAL_H_

extern void Uart1Init (void);
extern void Uart1PutCh (unsigned char ch);
extern void Uart1PutS (unsigned char *str);
extern unsigned char Uart1GetCh (void);

#endif 
