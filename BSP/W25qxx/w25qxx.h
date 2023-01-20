/*
 * @Author: LiuBT
 * @Date: 2022-02-23 09:42:01
 * @LastEditors: LiuBT
 * @LastEditTime: 2022-03-18 20:42:59
 * @FilePath: \MDK-ARMd:\desk\usb32\stm32_usb\Middlewares\Hardwere\inc\w25qxx.h
 * @Description: 
 * 
 */
#ifndef __W25QXX_H
#define __W25QXX_H
#include "stdint.h"
#include "main.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F103������
//W25QXX��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/5/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//W25Xϵ��/Qϵ��оƬ�б�	   
//W25Q80  ID  0XEF13
//W25Q16  ID  0XEF14
//W25Q32  ID  0XEF15
//W25Q64  ID  0XEF16	
//W25Q128 ID  0XEF17	
//W25Q256 ID  0XEF18
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17
#define W25Q256 0XEF18



#define   W25Q_OK                        ((uint8_t)0x00)
#define   W25Q_ERROR                     ((uint8_t)0x01)

#define W25QXX_CS_NON    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)
#define W25QXX_CS_OK     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)


////////////////////////////////////////////////////////////////////////////////// 
//ָ���
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg1		    0x05 
#define W25X_ReadStatusReg2		    0x35 
#define W25X_ReadStatusReg3		    0x15 
#define W25X_WriteStatusReg1      0x01 
#define W25X_WriteStatusReg2      0x31 
#define W25X_WriteStatusReg3      0x11 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F 
#define W25X_Enable4ByteAddr      0xB7
#define W25X_Exit4ByteAddr        0xE9

extern uint16_t W25QXX_TYPE;					//����W25QXXоƬ�ͺ�	

uint8_t W25QXX_Init(void);
uint16_t W25QXX_ReadID(void);  	    		//��ȡFLASH ID
uint8_t W25QXX_Get_State(void);
uint8_t W25QXX_Read_SR(uint8_t regno);             //��ȡ״̬�Ĵ��� 
void W25QXX_4ByteAddr_Enable(void);     //ʹ��4�ֽڵ�ַģʽ
void W25QXX_Write_SR(uint8_t regno,uint8_t sr);   //д״̬�Ĵ���
void W25QXX_Write_Enable(void);  		//дʹ�� 
void W25QXX_Write_Disable(void);		//д����
void W25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void W25QXX_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
void W25QXX_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
void W25QXX_Erase_Chip(void);    	  	//��Ƭ����
void W25QXX_Erase_Sector(uint32_t Dst_Addr);	//��������
void W25QXX_Wait_Busy(void);           	//�ȴ�����
void W25QXX_PowerDown(void);        	//�������ģʽ
void W25QXX_WAKEUP(void);				//����

#endif