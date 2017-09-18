#include <stm32f10x_lib.h>                           // stm32f10x definitions

#include "type.h"

#include "STM32_Init.h"                              // stm32 initialisation
#include "usbmem.h"

#include "lcd.h"

unsigned char IN_Buffer[512];
unsigned char OUT_Buffer[512]={"MIAT_STM32 DEMO"};

/* Main Program */

int main (void) 
{
  unsigned char *pIN_Buffer;
  unsigned short i;

  stm32_Init ();                                     // STM32 Initialization

  lcd_init();                                        // LCD Initialization
  lcd_clear();

  USB_SetOutBuffer(OUT_Buffer,512);
  USB_SetInBuffer(IN_Buffer,512);

  USB_Init();                                        // USB Initialization
  USB_Connect(TRUE);                                 // USB Connect

  while (1) 
  {                                        // Loop forever
    pIN_Buffer=IN_Buffer;
    set_cursor (0, 0);
    for(i=0;i<16;i++)
    {
      lcd_putchar(*pIN_Buffer++);  
    }
    set_cursor (0, 1);
    for(i=0;i<16;i++)
    {
      lcd_putchar(*pIN_Buffer++);  
    }
  } // end while
} // end main

