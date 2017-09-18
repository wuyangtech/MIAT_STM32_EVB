/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_FUNC_H
#define __LCD_FUNC_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_lib.h"
//#include "platform_config.h"

								  
//ErrorStatus HSEStartUpStatus;

#define en 		GPIO_Pin_8
#define rs      GPIO_Pin_9
#define rw		GPIO_Pin_10
 
/* Private function prototypes -----------------------------------------------*/
void init_lcd(void);

void delay(int d);
void en1(void);
void write_com(unsigned char c);
void write_data(unsigned char c);
void init_lcd(void);
void print(char line, char *str);
void prline1(char x, char w) ;
void prline2(char x, char w) ;

void clear(void);
void home(void);
void setCursor(char index);
void shiftDisplayLeft(void);
void shiftDisplayRight(void);

void pf4h(unsigned int value);
char tohex(unsigned char value);

#endif /* __LCD_FUNC_H */

