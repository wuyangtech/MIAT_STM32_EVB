/*  Initial System
* 	Tun-Kai Yao
*/	
#ifndef __INIT_SYS_H
#define __INIT_SYS_H

void SysTick_init(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void SPI1_Configuration(void);
void USART_Configuration(void);
void EXTI_Configuration(void);

#endif /* __INIT_SYS_H */
