/*** 
 * @Author: liubotao
 * @Date: 2023-01-19 01:58:32
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-20 01:13:45
 * @FilePath: \MINI-GUI\BSP\bsp.h
 * @Description: 
 * @
 */
#ifndef __BSP_H__
#define __BSP_H__


#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"
#include "oled.h"

extern OLED_t oledSSD1306;

void bsp_init(void);

#endif
