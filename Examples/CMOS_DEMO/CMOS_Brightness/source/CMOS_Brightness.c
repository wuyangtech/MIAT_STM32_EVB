#include <stm32f10x_lib.h>                           // stm32f10x definitions

#include "type.h"

#include "STM32_Init.h"                              // stm32 initialisation

#include "cmos.h"

#include "lcd.h"

#include "BasicIO.h"

unsigned char *CAM_Buffer;

/* Main Program */

int main (void) {
  unsigned short i,j;
  int G;
  int Dark,bright;
  short Interval;
  unsigned char KEY_Buffer,LED_Buffer;

  stm32_Init ();                                     // STM32 Initialization
  CMOS_Init();
  Init_BasicIO();

  lcd_init();                                        // LCD Initialization
  lcd_clear();
  lcd_print ("MIAT_STM32 DEMO ");

  CMOS_Exposure(0x0080);
  CMOS_SetWindowOrigin(578,810); //548,476
  CMOS_SetImageSize(128,128);

  bright=65535;
  Dark=0;

  while(1)
  {

    CAM_Buffer=(unsigned char *)0x60040000;

    CMOS_Capture(CAM_Buffer);

    CAM_Buffer=(unsigned char *)0x60040000;
    G=0;
    for(i=0;i<16;i++)
    {
      for(j=0;j<128;j+=8)
      {
        G+=CAM_Buffer[j];
      }
      CAM_Buffer+=1024;
    }

    KEY_Buffer=Key_Scan();
    if(KEY_Buffer==1)
    {
      Dark=G;
      set_cursor (0, 1);
      lcd_print ("Set Dark value  ");
    }
    else if(KEY_Buffer==2)
    {
      bright=G;
      set_cursor (0, 1);
      lcd_print ("Set bright value");
    }
    else if((bright-Dark)>0)
    {
      Interval=(bright-Dark)>>8;

      i=1;
      LED_Buffer=0;
      G-=Dark;
      while(G>0)
      {
        for(j=0;j<i;j++)
        {
      	  G-=Interval;
        }
        if(G>0)
        {
          LED_Buffer+=i;
    	  if(i>255)break;
        }
        else
        {
          G=0;
        }
  	    i<<=1;
      }
      LED_DATA_OUT(LED_Buffer);
      set_cursor (0, 1);
      lcd_print ("Display value   ");
    }
    else
    {
      set_cursor (0, 1);
      lcd_print ("Range Error     ");
    }
		
  }

} // end main
