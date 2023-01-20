#include "oled.h"
// #include "w25qxx.h"
#include "oledfont.h"
#include <string.h>

#ifdef SW_IIC

void IIC_Start()
{

	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}
void IIC_Stop()
{
	OLED_SCLK_Set();
	//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

void IIC_Wait_Ack()
{
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m, da;
	da = IIC_Byte;
	OLED_SCLK_Clr();
	for (i = 0; i < 8; i++)
	{
		m = da;
		//	OLED_SCLK_Clr();
		m = m & 0x80;
		if (m == 0x80)
		{
			OLED_SDIN_Set();
		}
		else
			OLED_SDIN_Clr();
		da = da << 1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}
// 向设备写控制命令
void OLED_WR_CMD(uint8_t cmd)
{
	// HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 0x100);
	IIC_Start();
	Write_IIC_Byte(0x78); // Slave address,SA0=0
	IIC_Wait_Ack();
	Write_IIC_Byte(0x00); // write command
	IIC_Wait_Ack();
	Write_IIC_Byte(cmd);
	IIC_Wait_Ack();
	IIC_Stop();
}
// 向设备写数据
void OLED_WR_DATA(uint8_t data)
{
	// HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
	IIC_Start();
	Write_IIC_Byte(0x78); // D/C#=0; R/W#=0
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40); // write data
	IIC_Wait_Ack();
	Write_IIC_Byte(data);
	IIC_Wait_Ack();
	IIC_Stop();
}
void OLED_WR_Byte(unsigned dat, unsigned cmd)
{
	if (cmd)
	{

		OLED_WR_DATA(dat);
	}
	else
	{
		OLED_WR_CMD(dat);
	}
}
#endif

struct OLED_Methods_t  methods;
void oledConstructor(OLED_t *const oled)
{
	methods.oledInit = oledInit;
	methods.oledClear = oledClear;
	methods.oledSetPos = oledSetPos;
	methods.oledDisplaySwitch = oledDisplaySwitch;
	methods.oledOn = oledOn;
	methods.oledShowNum = oledShowNum;
	methods.oledShowChar = oledShowChar;
	methods.oledShowString = oledShowString;
	methods.oledClearReverse = oledClearReverse;
	methods.oledRefreshBuffer = oledRefreshBuffer;

	oled->methods = &methods;
};

// 初始化oled屏幕
uint8_t Rebuf[128*8]={0};
uint8_t Rebuf2[128*8]={0};
void oledInit(OLED_t *oled)
{
	oled->oledHWInit();
	for (uint16_t i = 0; i < 128*8; i++)
	{
		Rebuf[i] = 0xff;
	}
	oled->delayMs(200);

	oled->oledWriteByte(oled->oledAddress, 0xAE, OLED_CMD); // 关闭显示

	oled->oledWriteByte(oled->oledAddress, 0x20, OLED_CMD); //---set low column address
	oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD); //---set high column address

	oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD); //---set low column address
	oled->oledWriteByte(oled->oledAddress, 0x10, OLED_CMD); //---set high column address

	oled->oledWriteByte(oled->oledAddress, 0x40, OLED_CMD); //---set low column address
	oled->oledWriteByte(oled->oledAddress, 0xB0, OLED_CMD); //---set high column address

	oled->oledWriteByte(oled->oledAddress, 0x81, OLED_CMD); // 设置对比度
	oled->oledWriteByte(oled->oledAddress, 0xFF, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xA1, OLED_CMD); // 段重定向设置
	oled->oledWriteByte(oled->oledAddress, 0xA6, OLED_CMD); //

	oled->oledWriteByte(oled->oledAddress, 0xA8, OLED_CMD); // 设置驱动路数
	oled->oledWriteByte(oled->oledAddress, 0x3F, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xC8, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0xD3, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xd8, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0x05, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xD9, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0xF1, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xDA, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0x12, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xDB, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0x30, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0x8d, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, 0x14, OLED_CMD);

	oled->oledWriteByte(oled->oledAddress, 0xaf, OLED_CMD);
	oledClear(oled);
}
// 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
void oledClear(OLED_t *oled)
{
	if (!oled->idleBuffer)
	{
		memset(oled->oledBuffer2, 0x00, oled->bufferSize);
		oled->idleBuffer = 1;
	}
	else
	{
		memset(oled->oledBuffer1, 0x00, oled->bufferSize);
		oled->idleBuffer = 0;
	}

	oled->oledWriteByte(oled->oledAddress, 0xb0, OLED_CMD); // 设置页地址（0~7）
	oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD); // 设置显示位置—列低地址
	oled->oledWriteByte(oled->oledAddress, 0x10, OLED_CMD); // 设置显示位置—列高地址

	// if (!oled->idleBuffer)
	// 	oled->oledWriteData(oled->oledAddress, oled->oledBuffer1, OLED_DATA, oled->bufferSize);
	// else
	// 	oled->oledWriteData(oled->oledAddress, oled->oledBuffer2, OLED_DATA, oled->bufferSize);
}

void oledClearReverse(OLED_t *oled)
{
	if (!oled->idleBuffer)
	{
		memset(oled->oledBuffer2, 0xff, oled->bufferSize);
		oled->idleBuffer = 1;
	}
	else
	{
		memset(oled->oledBuffer1, 0xff, oled->bufferSize);
		oled->idleBuffer = 0;
	}

	oled->oledWriteByte(oled->oledAddress, 0xb0, OLED_CMD); // 设置页地址（0~7）
	oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD); // 设置显示位置—列低地址
	oled->oledWriteByte(oled->oledAddress, 0x10, OLED_CMD); // 设置显示位置—列高地址

	// if (!oled->idleBuffer)
	// 	oled->oledWriteData(oled->oledAddress, oled->oledBuffer1, OLED_DATA, oled->bufferSize);
	// else
	// 	oled->oledWriteData(oled->oledAddress, oled->oledBuffer2, OLED_DATA, oled->bufferSize);
}

void oledSetPos(OLED_t *oled, unsigned char x, unsigned char y)
{
	oled->oledWriteByte(oled->oledAddress, 0xb0 + y, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, ((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	oled->oledWriteByte(oled->oledAddress, (x & 0x0f), OLED_CMD);
}
// 开启OLED显示
void oledDisplaySwitch(OLED_t *oled, uint8_t displaySwitch)
{
	if (displaySwitch)
	{
		oled->oledWriteByte(oled->oledAddress, 0X8D, OLED_CMD); // SET DCDC命令
		oled->oledWriteByte(oled->oledAddress, 0X14, OLED_CMD); // DCDC ON
		oled->oledWriteByte(oled->oledAddress, 0XAF, OLED_CMD); // DISPLAY ON
	}
	else
	{
		oled->oledWriteByte(oled->oledAddress, 0X8D, OLED_CMD); // SET DCDC命令
		oled->oledWriteByte(oled->oledAddress, 0X10, OLED_CMD); // DCDC OFF
		oled->oledWriteByte(oled->oledAddress, 0XAE, OLED_CMD); // DISPLAY OFF
	}
}

void oledOn(OLED_t *oled)
{
	uint8_t i, n;
	for (i = 0; i < 8; i++)
	{
		oled->oledWriteByte(oled->oledAddress, 0xb0 + i, OLED_CMD); // 设置页地址（0~7）
		oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD);		// 设置显示位置—列低地址
		oled->oledWriteByte(oled->oledAddress, 0x10, OLED_CMD);		// 设置显示位置—列高地址
		for (n = 0; n < 128; n++)
			oled->oledWriteByte(oled->oledAddress, 1, OLED_DATA);
	} // 更新显示
}
uint8_t oled_pow(uint8_t m, uint8_t n)
{
	unsigned int result = 1;
	while (n--)
		result *= m;
	return result;
}

void oledRefreshBuffer(OLED_t *oled)
{
	oled->oledWriteByte(oled->oledAddress, 0xb0, OLED_CMD); // 设置页地址（0~7）
	oled->oledWriteByte(oled->oledAddress, 0x00, OLED_CMD); // 设置显示位置—列低地址
	oled->oledWriteByte(oled->oledAddress, 0x10, OLED_CMD); // 设置显示位置—列高地址

	if (!oled->idleBuffer)
	{
		oled->idleBuffer = 1;//如果buffer1（0） 是空闲 则刷新0 并且设置位忙
		oled->oledWriteData(oled->oledAddress, oled->oledBuffer1, OLED_DATA, oled->bufferSize);

	}
	else
	{
		oled->idleBuffer = 1; // 如果buffer2（2） 是空闲 则刷新0 并且设置位忙
		oled->oledWriteData(oled->oledAddress, oled->oledBuffer2, OLED_DATA, oled->bufferSize);
	}
}

// 显示2个数字
// x,y :起点坐标
// len :数字的位数
// size:字体大小
// mode:模式	0,填充模式;1,叠加模式
// num:数值(0~4294967295);
void oledShowNum(OLED_t *oled, uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size2)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				oledShowChar(oled, x + (size2 / 2) * t, y, ' ', size2);
				continue;
			}
			else
				enshow = 1;
		}
		oledShowChar(oled, x + (size2 / 2) * t, y, temp + '0', size2);
	}
}
// 在指定位置显示一个字符,包括部分字符
// x:0~127
// y:0~63
// mode:0,反白显示;1,正常显示
// size:选择字体 16/12
void oledShowChar(OLED_t *oled, uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
{
	unsigned char c = 0, i = 0;
	c = chr - ' '; // 得到偏移后的值
	if (x > 128 - 1)
	{
		x = 0;
		y = y + 2;
	}
	if (Char_Size == 16)
	{
		oledSetPos(oled, x, y);
		for (i = 0; i < 8; i++)
			oled->oledWriteByte(oled->oledAddress, F8X16[c * 16 + i], OLED_DATA);
		// OLED_WR_DATA(F8X16[c * 16 + i]);
		oledSetPos(oled, x, y + 1);
		for (i = 0; i < 8; i++)
			oled->oledWriteByte(oled->oledAddress, F8X16[c * 16 + i + 8], OLED_DATA);
	}
	else
	{
		oledSetPos(oled, x, y);
		for (i = 0; i < 6; i++)
			oled->oledWriteByte(oled->oledAddress, F6x8[c][i], OLED_DATA);
	}
}

// 显示一个字符号串
void oledShowString(OLED_t *oled, uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		oledShowChar(oled, x, y, chr[j], Char_Size);
		x += 8;
		if (x > 120)
		{
			x = 0;
			y += 2;
		}
		j++;
	}
}

/*
void LCD_CharDot(uint8_t *dot, uint8_t c) {

	uint8_t p = 0x01;        //像素点控制，

	KS_GRAM;                 //LCD RAM入口


	if (c > 1) {
		p = 0x80;            //这与点阵字体的存储方式有关
		for (uint8_t i = PrintInit.size_H; i > 0; i--) {      //打印点阵行控制
			for(uint8_t j = PrintInit.size_L / 8; j > 0; j--){           //打印点阵列控制
			while (p) {
	   if(*dot&p)
		  W_GRAM = PrintInit.pen;           //字体打印
	   else
		  W_GRAM = PrintInit.backC;         //底色打印

			   p = p >> 1;
			}

				p = 0x80;
			dot++;
		}

		}
	}


	else {
		for (uint8_t i = PrintInit.size_H; i > 0; i--) {

	   for(uint8_t j = PrintInit.size_L / 16; j > 0; j--){
			while (p) {
	 if(*dot&p)
	   W_GRAM = PrintInit.pen;        //字体打印
	 else
	   W_GRAM = PrintInit.backC;      //底色打印
	   p = p << 1;
			}
				p = 0x01;
			  dot++;
		}
		}
	}
}

uint32_t CN_PYL;
uint32_t CH_PYL;
void LCD_print(uint8_t x,uint8_t y,uint8_t *string) {
	uint8_t dot[128];           //临时存储 用来存储从Flash中读出的字符点阵数据
	uint8_t GBK_H, GBK_L;       //GBK编码 高字节 和低字节
	uint32_t GBK;               //字符点阵在flash中的地址
	uint16_t ax = x;         //字符打印位置控制 X方向
	uint16_t ay = y;         //字符打印位置控制 Y方向
	while (*string!='\0') {
		GBK_H = *string;

		if(*string=='\n'){
	 y = y + (2 + 16) - 1;
		}

		else{


		if (GBK_H > 0x80) {
			GBK_L = *(++string);

			GBK_H -= 0x81;

			if (GBK_L > 0x7f)
				GBK_L -= 0x41;
			else
				GBK_L -= 0x40;

			GBK = ((uint32_t)190 * GBK_H + GBK_L) * CN_PYL+ (uint32_t)CH_PYL * 96 ;      //计算所打印的字符在Flash字库存储的位置
			W25QXX_Read(dot, GBK,  CN_PYL);   //读取flash
			//FLASH_Read_Data(dot, GBK,  CN_PYL);                                        //从Flash字库中读取字符点阵存放到dot数组中
	  OLED_Set_Pos(x,y);
			//LCD_Window(x, x + 15 - 1, y, y + 16 - 1);      //设置打印窗口
			//LCD_X_Y(x, y);                                                             //设置打印起始地址
			//LCD_CharDot(dot, 2);                                               //打印字符
	  //OLED_WR_DATA(dot());
			OLED_ShowCHinese(x,y,dot);
			ax = ax + (15 - 1 +2);                     //调整字距字距

			if ((239 - x < 15 || x >= 239) && 1) {                   //检测本行是否无法显示所有内容，判断是否要自动换行
				ax = x,ay = y + (2 + 16) - 1;
		}
	}





		string++;
	}
	}
显示汉字
hzk 用取模软件得出的数组
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t *no)
{
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);
	for(t=0;t<16;t++)
		{
				OLED_WR_DATA(Hzk[2*16][t]);
				adder+=1;
	 }
		OLED_Set_Pos(x,y+1);
	for(t=0;t<16;t++)
			{
			//	OLED_WR_DATA(Hzk[2*no+1][t]);
				adder+=1;
	  }
}
*/

///*******************************************************************************
// 函 数 名         : void OLED_Show_str(uint8_t row,uint8_t colon,uint8_t* str,uint8_t mode)
// 函数功能			 : 显示中英文混合字串
// 输    入         : row行，colon列,str字符串，mode显示模式（1汉字反白显示）
// 输    出         : 无
// 说    明         : 1.ASII字符不会反白显示，2.行列输入可以超过8，128，超过时会换行回环显示,但建议不要使用过大；
//*******************************************************************************/
// void OLED_Show_str(uint8_t row,uint16_t colon,uint8_t* str,uint8_t mode)
//{
//    uint8_t is_Hz=0;     //字符或者中文
//	uint8_t size =16;
//    while(*str!=0)//数据未结束
//    {
//		if(colon>=128)//换行
//		{
//			row+=2*(colon/128);colon%=128;
//			if(row>=8)row%=8;//溢出回环重显
//		}
//        if(!is_Hz)
//        {
//	        if(*str>0x80)is_Hz=1;//标记为中文
//	        else              //字符处理
//	        {
//						OLED_ShowChar(colon,row,*str,16);
//				//OLED_DISPLAY_8x16(row,colon,*str);//字符写入
//				str++;
//		        colon+=size/2; //字符,为全字的一半
//	        }
//        }else//中文
//        {
//            is_Hz=0;//清零变量用于下一次识别
//	        OLED_Show_HZ(colon,row,str,mode); //显示这个汉字,
//	        str+=2;
//	        colon+=size;//下一个汉字偏移
//        }
//    }
//}

///*******************************************************************************
// 函 数 名         : void OLED_Show_HZ(uint8_t x,uint8_t y,uint8_t*ZH,uint8_t mode)
// 函数功能			 : 显示一个中文GBK16字符
// 输    入         : x行，y列，ZH,单个汉字的字符串，mode模式（1反白显示）
// 输    出         : 无
// 说    明         : 注意x是行，不是x指横轴（我写的坑，懒得修了）
//*******************************************************************************/
// void OLED_Show_HZ(uint8_t x,uint8_t y,uint8_t*ZH,uint8_t mode)
//{
//	uint8_t i=0;
//	uint8_t j,t,c=0;
//	uint8_t dzk[32];
//	Get_HzMat(ZH,dzk);
//	for(i=0;i<32;i++)
//	{
//		if(mode)dzk[i] =~( char_revolve(dzk[i]) ) ;//mode1,反白显示；
//		else dzk[i] = char_revolve(dzk[i]);
//	}
//	for(t=0;t<2;t++)
//	{
//		OLED_Set_Pos(x,y);
//		for(j=0;j<16;j++)
//		{ //整页内容填充
//			if(t==0){c=2*j;}
//			else {c=2*j+1;}
// 			OLED_WR_DATA(dzk[c]);
//		}y++; //页地址加1
//	}
//	//I2C_SAND_BYTE(OLED0561_ADD,COM,0xAF); //开显示
//}

///*******************************************************************************
// 函 数 名         : static uint8_t char_revolve(uint8_t temp_char)
// 函数功能			 : 字节1反序函数
// 输    入         : 供 void OLED_Show_HZ(uint8_t x,uint8_t y,uint8_t*ZH,uint8_t mode) 显示GBK16字库字符使用
// 输    出         : 反序后的GBK16码表值
// 说    明         : 无
//*******************************************************************************/
// static uint8_t char_revolve(uint8_t temp_char)
//{
//	uint8_t result=0;
//	uint8_t i=0;
//	uint8_t Mask_bit=0x01;
//	for(i=0;i<8;i++)
//	{
//		if(temp_char&0x80)result|=Mask_bit;
//		temp_char<<=1;
//		Mask_bit<<=1;
//	}
//	return result;
//}
////code 字符指针开始
////从字库中查找出字模
////code 字符串的开始地址,GBK码
////mat  数据存放地址 (size/8+((size%8)?1:0))*(size) bytes大小
////size:字体大小
// void Get_HzMat(unsigned char *code,unsigned char *mat)
//{
//	unsigned char qh,ql;
//	unsigned char i;
//	unsigned long foffset;
//	uint8_t size=16;
//	uint8_t csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数
//	qh=*code;
//	ql=*(++code);
//	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//非 常用汉字
//	{
//	    for(i=0;i<csize;i++)*mat++=0x00;//填充满格
//	    return; //结束访问
//	}
//	if(ql<0x7f)ql-=0x40;//注意!
//	else ql-=0x41;
//	qh-=0x81;
//	foffset=((unsigned long)190*qh+ql)*csize;	//得到字库中的字节偏移量
//
//			W25QXX_Read(mat,foffset,32);
//
//			/*+ftinfo.f16addr*/
//
// }
