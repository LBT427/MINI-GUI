/*** 
 * @Author: liubotao
 * @Date: 2023-01-19 01:14:16
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-20 04:02:58
 * @FilePath: \MINI-GUI\BSP\OLED_ssd1306\oled.h
 * @Description: 
 * @
 */

#ifndef __OLED_H__
#define __OLED_H__
#include "main.h"
#include "gpio.h"
// #define OLED_SCLK_Clr()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
// //GPIO_ResetBits(GPIOB,GPIO_Pin_6)//SDA IIC接口的时钟信号
// #define OLED_SCLK_Set()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
//GPIO_SetBits(GPIOB,GPIO_Pin_6)

// #define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,GPIO_PIN_RESET);//GPIO_ResetBits(GPIOB,GPIO_Pin_5)//SCL IIC接口的数据信号
// #define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,GPIO_PIN_SET);//GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//void WriteCmd();
// void OLED_WR_CMD(uint8_t cmd);
// void OLED_WR_DATA(uint8_t data);
// void OLED_WR_Byte(unsigned dat,unsigned cmd);
// void Write_IIC_Byte(unsigned char IIC_Byte);
// void OLED_Init(void);
// void OLED_Clear();
// void OLED_Display_On(void);
// void OLED_Display_Off(void);
// void OLED_Set_Pos(uint8_t x, uint8_t y) ;
// void OLED_On(void);
// unsigned int oled_pow(uint8_t m,uint8_t n);
// void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2);
// void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
// void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);
// //void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t *no);
// void OLED_Show_HZ(uint8_t x,uint8_t y,uint8_t*ZH,uint8_t mode);
// void Get_HzMat(unsigned char *code,unsigned char *mat);
// void OLED_Show_str(uint8_t row,uint16_t colon,uint8_t* str,uint8_t mode);
// static uint8_t char_revolve(uint8_t temp_char);

struct OLED_Methods_t;

typedef struct 
{
    char screenName[20];
    uint8_t oledAddress;

    uint16_t width;
    uint16_t height;

    uint8_t *oledBuffer1;
    uint8_t *oledBuffer2;
    uint8_t idleBuffer;
    uint16_t bufferSize;

    void (*oledHWInit)(void);
    int8_t (*oledWriteByte)(uint8_t DevAddress, uint8_t data, uint8_t cmd);
    int8_t (*oledWriteData)(uint8_t DevAddress, uint8_t *data, uint8_t cmd, uint8_t num);
    void (*delayMs)(uint16_t ms);

    struct OLED_Methods_t * methods;

}OLED_t;





void oledInit(OLED_t *oled);
void oledClear(OLED_t *oled);
void oledSetPos(OLED_t *oled, unsigned char x, unsigned char y);
void oledDisplaySwitch(OLED_t *oled, uint8_t displaySwitch);
void oledOn(OLED_t *oled);
uint8_t oled_pow(uint8_t m, uint8_t n);
void oledShowNum(OLED_t *oled, uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size2);
void oledShowChar(OLED_t *oled, uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);
void oledShowString(OLED_t *oled, uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size);
void oledClearReverse(OLED_t *oled);
void oledRefreshBuffer(OLED_t *oled);

struct OLED_Methods_t
{
    void (*oledInit)(OLED_t *const oled);
    void (*oledClear)(OLED_t *const oled);
    void (*oledSetPos)(OLED_t *const oled, unsigned char x, unsigned char y);
    void (*oledDisplaySwitch)(OLED_t *const oled, uint8_t displaySwitch);
    void (*oledOn)(OLED_t *const oled);
    void (*oledShowNum)(OLED_t *const oled, uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size2);
    void (*oledShowChar)(OLED_t *const oled, uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);
    void (*oledShowString)(OLED_t *const oled, uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size);
    void (*oledClearReverse)(OLED_t *const oled);
    void (*oledRefreshBuffer)(OLED_t *const oled);
};

void oledConstructor(OLED_t *const oled);


#endif 


