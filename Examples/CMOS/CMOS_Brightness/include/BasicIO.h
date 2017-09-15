#ifndef __BasicIO_H
#define __BasicIO_H

#define KEY ((GPIOB->IDR & 0x01E0) >> 5)

#define KEY1 ((GPIOB->IDR & 0x0020) >> 5)
#define KEY2 ((GPIOB->IDR & 0x0040) >> 6)
#define KEY3 ((GPIOB->IDR & 0x0080) >> 7)
#define KEY4 ((GPIOB->IDR & 0x0100) >> 8)

#define LED_DATA (0xFF <<  8)

#define LED_DATA_OUT(x)       GPIOG->ODR = (GPIOG->ODR & ~LED_DATA) | ((x & 0xFF) << 8);

#define SW ((GPIOC->IDR & 0x0F00) >> 8)

void Init_BasicIO(void);
unsigned char Key_Scan(void);

#endif
/******************************************************************************/
