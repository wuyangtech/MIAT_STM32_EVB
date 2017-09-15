/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main program body.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_lib.h"
//#include "platform_config.h"

#include "hw_config.h"
#include "lcd_func.h"

extern vu16 ADCConvertedValue;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************

* Function Name  : main

* Description    : Main program

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/
int main(void)
{


#ifdef DEBUG

  debug();

#endif


  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_Configuration();

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_Configuration();

  /* ªì©l¤Æ LCD ¤¶­±  */
  init_lcd();


   clear();
   while(1)
   {
      pf4h(ADCConvertedValue);
   	  delay(10000);

   }

}


