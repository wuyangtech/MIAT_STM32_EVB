#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((u32)0x4001244C)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

ADC_InitTypeDef ADC_InitStructure;

DMA_InitTypeDef DMA_InitStructure;

vu16 ADCConvertedValue;

ErrorStatus HSEStartUpStatus;

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************

* Function Name  : DMA1 chagnel1 Configuration

* Description    : configuration the DMA

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/

void DMA_Configuration(void)
{

  DMA_DeInit(DMA1_Channel1);

  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;

  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADCConvertedValue;

  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

  DMA_InitStructure.DMA_BufferSize = 1;

  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;

  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;

  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

  DMA_InitStructure.DMA_Priority = DMA_Priority_High;

  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  

  /* Enable DMA1 channel1 */

  DMA_Cmd(DMA1_Channel1, ENABLE);


}



/*******************************************************************************

* Function Name  : ADC1_Configuration

* Description    : configuration the DMA

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/

void ADC_Configuration(void)

{

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;

  ADC_InitStructure.ADC_ScanConvMode = ENABLE;

  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

  ADC_InitStructure.ADC_NbrOfChannel = 1;

  ADC_Init(ADC1, &ADC_InitStructure);


  /* ADC1 regular channel10 configuration */ 

  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);


  /* Enable ADC1 DMA */

  ADC_DMACmd(ADC1, ENABLE);

  

  /* Enable ADC1 */

  ADC_Cmd(ADC1, ENABLE);


  /* Enable ADC1 reset calibaration register */   

  ADC_ResetCalibration(ADC1);

  /* Check the end of ADC1 reset calibration register */

  while(ADC_GetResetCalibrationStatus(ADC1));


  /* Start ADC1 calibaration */

  ADC_StartCalibration(ADC1);

  /* Check the end of ADC1 calibration */

  while(ADC_GetCalibrationStatus(ADC1));

     

  /* Start ADC1 Software Conversion */ 

  ADC_SoftwareStartConvCmd(ADC1, ENABLE);


}

/*******************************************************************************

* Function Name  : RCC_Configuration

* Description    : Configures the different system clocks.

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/

void RCC_Configuration(void)

{

  /* RCC system reset(for debug purpose) */

  RCC_DeInit();


  /* Enable HSE */

  RCC_HSEConfig(RCC_HSE_ON);


  /* Wait till HSE is ready */

  HSEStartUpStatus = RCC_WaitForHSEStartUp();


  if(HSEStartUpStatus == SUCCESS)

  {

    /* Enable Prefetch Buffer */

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);


    /* Flash 2 wait state */

    FLASH_SetLatency(FLASH_Latency_2);

  

    /* HCLK = SYSCLK */

    RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  

    /* PCLK2 = HCLK */

    RCC_PCLK2Config(RCC_HCLK_Div1); 


    /* PCLK1 = HCLK/2 */

    RCC_PCLK1Config(RCC_HCLK_Div2);


    /* ADCCLK = PCLK2/4 */

    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 

  

    /* PLLCLK = 8MHz * 7 = 56 MHz */

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);


    /* Enable PLL */ 

    RCC_PLLCmd(ENABLE);


    /* Wait till PLL is ready */

    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)

    {

    }


    /* Select PLL as system clock source */

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);


    /* Wait till PLL is used as system clock source */

    while(RCC_GetSYSCLKSource() != 0x08)

    {

    }

  }


/* Enable peripheral clocks --------------------------------------------------*/

  /* Enable DMA1 clock */

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);


  /* Enable ADC1 and GPIOA clock */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);


  /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


}


/*******************************************************************************

* Function Name  : GPIO_Configuration

* Description    : Configures the different GPIO ports.

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/

void GPIO_Configuration(void)

{

  GPIO_InitTypeDef GPIO_InitStructure;


  /*Configure PA.0 (ADC Channel0) as analog input -------------------------*/

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure); 



  /* Configure IO connected to GPIOC *********************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | 
                                GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | 
								GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | 
								GPIO_Pin_9 | GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);



}


/*******************************************************************************

* Function Name  : NVIC_Configuration

* Description    : Configures Vector Table base location.

* Input          : None

* Output         : None

* Return         : None

*******************************************************************************/

void NVIC_Configuration(void)

{

#ifdef  VECT_TAB_RAM  

  /* Set the Vector Table base location at 0x20000000 */ 

  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 

#else  /* VECT_TAB_FLASH  */

  /* Set the Vector Table base location at 0x08000000 */ 

  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   

#endif

}

