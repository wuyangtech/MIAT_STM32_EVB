#include <stm32f10x_lib.h>                           // stm32f10x definitions

#include "type.h"

#include "STM32_Init.h"                              // stm32 initialisation

#include "cmos.h"

#include "lcd.h"

#include "BasicIO.h"

unsigned char *CAM_Buffer;
unsigned char KEY_Buffer;

/* Main Program */

int main (void) 
{
  unsigned char i,j;
  int R,G,B;

  stm32_Init ();                                     // STM32 Initialization
  CMOS_Init();
  Init_BasicIO();

  lcd_init();                                        // LCD Initialization
  lcd_clear();
  lcd_print ("MIAT_STM32 DEMO ");

  CMOS_Exposure(0x0080);
  CMOS_SetWindowOrigin(578,810); //548,476
  CMOS_SetImageSize(128,128);

  while(1)
  {
    KEY_Buffer=Key_Scan();
	if(KEY_Buffer==1)
	{
      CAM_Buffer=(unsigned char *)0x60040000;

      CMOS_Capture(CAM_Buffer);

      CAM_Buffer=(unsigned char *)0x60040000;
      R=0;
      G=0;
      B=0;
      for(i=0;i<16;i++)
      {
        for(j=0;j<128;j+=8)
        {
          G+=CAM_Buffer[j];
        }
        for(j=1;j<128;j+=8)
        {
          R+=CAM_Buffer[j];
        }
        CAM_Buffer+=128;
        for(j=0;j<128;j+=8)
        {
          B+=CAM_Buffer[j];
        }
        CAM_Buffer+=896;
      }

      if(((G-R)>800) && ((G-B)>1000))
      {
        set_cursor (0, 1);
        lcd_print ("Color is Green  ");
      }
      else if(((R-G)>1000) && ((R-B)>1000))
      {
        set_cursor (0, 1);
        lcd_print ("Color is Red    ");
      }
      else if(((B-R)>1000) && ((B-G)>1000))
      {
        set_cursor (0, 1);
        lcd_print ("Color is Blue   ");
      }
      else
      {
        set_cursor (0, 1);
        lcd_print ("Color is Unknow ");
      }
    }
    else if(KEY_Buffer==2)
    {
        set_cursor (0, 1);
        lcd_print ("CLEAR           ");
    }
  }

} // end main
