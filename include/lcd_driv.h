
#ifndef LCD_DRIV_H
#define LCD_DRIV_H

#define LCD 0xFF<<16
#define RS 1<<13
#define RW 1<<14
#define E 1<<15
extern void comd(unsigned char );
extern void data(unsigned int );
extern void delay_fv(unsigned int ,int );
extern void lcd_init(void); 
extern void send_string_to_lcd(char *);
extern void lcd_2nd_line(void);
extern void lcd_1st_line(void);
extern void lcd_clean(void);

#endif
