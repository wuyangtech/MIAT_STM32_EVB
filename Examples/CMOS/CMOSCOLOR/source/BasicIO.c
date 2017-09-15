/* Includes ------------------------------------------------------------------*/
#include <stm32f10x_lib.h>              /* STM32F10x Library Definitions      */
#include "BasicIO.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void BasicIO_GPIO_Configuration(void);
void BasicIO_Configuration(void);

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure the used I/O ports pin
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BasicIO_GPIO_Configuration(void)
{
  RCC->APB2ENR |= 0x00000118;                

  GPIOB->CRL &= ~0xFFF00000;
  GPIOB->CRL |=  0x44400000;
  GPIOB->CRH &= ~0x0000000F;
  GPIOB->CRH |=  0x00000004;
  GPIOC->CRH &= ~0x0000FFFF;
  GPIOC->CRH |=  0x00004444;
  GPIOG->CRH &= ~0xFFFFFFFF;
  GPIOG->CRH |=  0x33333333;
}

/*******************************************************************************
* Function Name  : BasicIO_Configuration
* Description    : BasicIO Configuration
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BasicIO_Configuration(void)
{
  LED_DATA_OUT(0x00);
}

/*******************************************************************************
* Function Name  : Init_BasicIO
* Description    : Initializes peripherals used by the BasicIO.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Init_BasicIO(void)
{
  /* GPIO configuration */
  BasicIO_GPIO_Configuration();

  /* I2C configuration */
  BasicIO_Configuration();
}

/*******************************************************************************
* Function Name  : Key_Scan
* Description    : 
* Input          : 
* Output         : unsigned char
* Return         : None
*******************************************************************************/
unsigned char Key_Scan(void)
{
//	unsigned char temp;
	if(KEY1 == 0)
	{
		return 1;
	}
	else if(KEY2 == 0)
	{
		return 2;
	}
	else if(KEY3 == 0)
	{
		return 3;
	}
	else if(KEY4 == 0)
	{
		return 4;
	}
	else
	{		
		return 0xFF;
	}
}

