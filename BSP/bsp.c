/*
 * @Author: liubotao
 * @Date: 2023-01-19 01:58:49
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-20 04:01:02
 * @FilePath: \MINI-GUI\BSP\bsp.c
 * @Description:
 *
 */
#include "bsp.h"

#define HW_IIC_DMA

void ssd1306HardwareInit(void)
{
    MX_SPI1_Init();
}

int8_t ssd1306WriteByte(uint8_t DevAddress, uint8_t data, uint8_t cmd)
{
    if (cmd)
        return HAL_I2C_Mem_Write(&hi2c1, DevAddress, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
    else
        return HAL_I2C_Mem_Write(&hi2c1, DevAddress, 0x00, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
}

int8_t ssd1306WriteData(uint8_t DevAddress, uint8_t *data, uint8_t cmd, uint8_t num)
{

#ifdef HW_IIC_NODMA
    if (cmd)
        return HAL_I2C_Mem_Write(&hi2c1, DevAddress, 0x40, I2C_MEMADD_SIZE_8BIT, data, num, 1000);
    else
        return HAL_I2C_Mem_Write(&hi2c1, DevAddress, 0x00, I2C_MEMADD_SIZE_8BIT, data, num, 1000);
#endif
#ifdef HW_IIC_DMA
    if (cmd)
    {
        while (hi2c1.State != HAL_I2C_STATE_READY);
        HAL_I2C_Mem_Write_DMA(&hi2c1, DevAddress, 0x40, I2C_MEMADD_SIZE_8BIT, data, 128 * 8);
    }
    else
    {
        while (hi2c1.State != HAL_I2C_STATE_READY);
        HAL_I2C_Mem_Write_DMA(&hi2c1, DevAddress, 0x00, I2C_MEMADD_SIZE_8BIT, data, 128 * 8);
    }
#endif
}

uint8_t displayBuffer1[128 * 8] = {0};
uint8_t displayBuffer2[128 * 8] = {0};

OLED_t oledSSD1306 = {
    .screenName = "SSD1306_0.96",
    .oledAddress = 0x78,
    .width = 128,
    .height = 64,
    .oledBuffer1 = displayBuffer1,
    .oledBuffer2 = displayBuffer2,
    .idleBuffer = 0,
    .bufferSize = 128*8,
    .oledHWInit = ssd1306HardwareInit,
    .oledWriteByte = ssd1306WriteByte,//传输单字节数据
    .oledWriteData = ssd1306WriteData,//传输大量数据
    .delayMs = HAL_Delay,
};





void bsp_init(void)
{
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_I2C1_Init();
    
    MX_TIM2_Init();
    MX_USART1_UART_Init();
    
    oledConstructor(&oledSSD1306);
    oledSSD1306.methods->oledInit(&oledSSD1306);
    //oledInit(&oledSSD1306);
    oledSSD1306.methods->oledShowString(&oledSSD1306,0,0,"hello",12);
    HAL_Delay(500);
}
