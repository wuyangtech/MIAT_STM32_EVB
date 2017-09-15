/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __CMOS_H
#define __CMOS_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x_lib.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CMOS_Init(void);
void CMOS_Exposure(unsigned short Shutter_Width);
void CMOS_SetWindowOrigin(unsigned short Row_Start, unsigned short Column_Start);
void CMOS_SetImageSize(unsigned short Row_Width, unsigned short Column_Width);
void CMOS_Capture(unsigned char *CAM_Buffer);

#endif /* __CMOS_H */


