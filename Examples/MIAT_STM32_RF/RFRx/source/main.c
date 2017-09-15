/*
*  nRF Transmitter
*  Auther    Lin Li 2008/11/27
*  Modeified Tun-Kai Yao 2009/06/14 
*            -- a. include new library and new startup code
*            -- b.  
*
*/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "stm32f10x_lib.h"
#include "init_sys.h"
#include "timedelay.h"
#include "rf_ctrl.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
u8 rfrx_payload[32];

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
int i;
RF_ConfTypeDef rfInitConfigure;

#ifdef DEBUG
  debug();
#endif

	
    RCC_Configuration();
	NVIC_Configuration();
    GPIO_Configuration();
    SysTick_init();
	SPI1_Configuration();
    USART_Configuration();
    EXTI_Configuration();	
    printf("[STM32F103] System Bootup\n\r");

    /* Infinite loop */
    //while(1){
		for(i=0;i<100;i++) Delay(200);
		
		RF_ConfigureMode();
		RF_FlushTxBuf();
		RF_FlushRxBuf();
        
		rfInitConfigure.AddressWidth = 3;     // Setuo Rx/Tx address width
		rfInitConfigure.RxAddress[0] = 0xE7;  // Rx Address
		rfInitConfigure.RxAddress[1] = 0xE7;  
		rfInitConfigure.RxAddress[2] = 0xE7;
		rfInitConfigure.RxAddress[3] = 0xE7;
		rfInitConfigure.RxAddress[4] = 0xE7;
		rfInitConfigure.TxAddress[0] = 0xE7;  // Tx Address
		rfInitConfigure.TxAddress[1] = 0xE7;
		rfInitConfigure.TxAddress[2] = 0xE7;
		rfInitConfigure.TxAddress[3] = 0xE7;
		rfInitConfigure.TxAddress[4] = 0xE7;
		rfInitConfigure.DataLengthPipe0	= 32;
		rfInitConfigure.Config = 0x0f;		  // PWR_UP | CRC(2Byte) | Prim Tx
		rfInitConfigure.AutoAck = 0x01;		  // Auto Ack
		rfInitConfigure.RxPipe = 0x01;		  // Enable pipe0
		rfInitConfigure.Retry = 0x0a;		  // 10 retrans
		rfInitConfigure.Channel = 0x09;		  // Channel
		rfInitConfigure.Setup = 0x0f;		  // Tx_PWR: 0dbm | DataRate: 2Mbps | LAN: HCURR
		rfInitConfigure.Status = 0x70;		  // Read Status | Clear IRQ Flag
		rfInitConfigure.ObserveTx = 0x00;

		RF_Init(&rfInitConfigure);

        RF_NormalMode();

		printf("[STM32F103] RF Receiver Service Ready\n\r");
		while(1){
		    
		}		
	//}
}

PUTCHAR_PROTOTYPE
{
    /* Write a character to the USART */
    USART_SendData(USART1, (u8) ch);

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}



#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
