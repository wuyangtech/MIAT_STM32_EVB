#include <stm32f10x_lib.h>                           // stm32f10x definitions

#include "type.h"

#include "STM32_Init.h"                              // stm32 initialisation
#include "usbmem.h"

#include "cmos.h"

#include "USBMemCam.h"

unsigned char CAM_Buffer[200][768];

/* Main Program */

int main (void) {
  stm32_Init ();                                     // STM32 Initialization
  CMOS_Init();
  CMOS_Exposure(0x0040);
  CMOS_SetWindowOrigin(548,476); //548,476
  CMOS_SetImageSize(200,768);


  UBS_SetBuffer(&CAM_Buffer[0][0],153600);
  UBS_GetBuffer(CMOS_Capture);

  USB_Init();                                        // USB Initialization
  USB_Connect(TRUE);                                 // USB Connect

  while (1) {                                        // Loop forever
    ;
  } // end while
} // end main

