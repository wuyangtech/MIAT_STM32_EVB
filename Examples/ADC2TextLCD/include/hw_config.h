/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_lib.h"
#include "platform_config.h"


 
/* Private function prototypes -----------------------------------------------*/
void DMA_Configuration(void);
void ADC_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

#endif /*_HW CONFIG_H */

