#ifndef __RF_SPI_H
#define __RF_SPI_H

#include "stm32f10x_lib.h"

u8 spi_push(u8 data);
u8 spi_push_reg(u8 reg, u8 value);
u8 spi_write_buf(u8 reg, u8 *pBuf, u8 bytes);
u8 spi_read_buf(u8 reg, u8 *pBuf, u8 bytes);

#endif /* __RF_SPI_H */


