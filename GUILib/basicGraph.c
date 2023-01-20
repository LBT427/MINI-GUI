/*
 * @Author: liubotao
 * @Date: 2023-01-20 13:46:17
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-20 16:57:54
 * @FilePath: \MINI-GUI\GUILib\basicGraph.c
 * @Description: 
 * 
 */
#include "basicGraph.h"


//功能:清除屏幕缓冲数据
void ClearScreenBuffer(unsigned char val)
{
  memset(ScreenBuffer, val, sizeof(ScreenBuffer));
}



//点
//设置当前选择的缓冲区 的 某一个点的亮灭
void SetPointBuffer(int x, int y, int value)
{
  if (x > SCREEN_COLUMN - 1 || y > SCREEN_ROW - 1) //超出范围
    return;

  if (value)
    ScreenBuffer[y / SCREEN_PAGE_NUM][x] |= 1 << (y % SCREEN_PAGE_NUM);
  else
    ScreenBuffer[y / SCREEN_PAGE_NUM][x] &= ~(1 << (y % SCREEN_PAGE_NUM));
}

//线

// 交换整数 a 、b 的值
inline void swap_int(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
 
// Bresenham's line algorithm
void draw_line(IMAGE *img, int x1, int y1, int x2, int y2, unsigned long c) {
    // 参数 c 为颜色值
    int dx = abs(x2 - x1),
        dy = abs(y2 - y1),
        yy = 0;
 
    if (dx < dy) {
        yy = 1;
        swap_int(&x1, &y1);
        swap_int(&x2, &y2);
        swap_int(&dx, &dy);
    }
 
    int ix = (x2 - x1) > 0 ? 1 : -1,
         iy = (y2 - y1) > 0 ? 1 : -1,
         cx = x1,
         cy = y1,
         n2dy = dy * 2,
         n2dydx = (dy - dx) * 2,
         d = dy * 2 - dx;
 
    if (yy) { // 如果直线与 x 轴的夹角大于 45 度
        while (cx != x2) {
            if (d < 0) {
                d += n2dy;
            } else {
                cy += iy;
                d += n2dydx;
            }
            putpixel(img, cy, cx, c);
            cx += ix;
        }
    } else { // 如果直线与 x 轴的夹角小于 45 度
        while (cx != x2) {
            if (d < 0) {
                d += n2dy;
            } else {
                cy += iy;
                d += n2dydx;
            }
            putpixel(img, cx, cy, c);
            cx += ix;
        }
    }
}

//面 
//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//得到填充的宽度
	height=ey-sy+1;			//高度
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)LCD_WR_DATA(color[i*width+j]);//写入数据 
	}	  
} 

//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//三角 
//多边形 



//圆 
// 八对称性
inline void _draw_circle_8(IMAGE *img, int xc, int yc, int x, int y, unsigned long c) {
    // 参数 c 为颜色值
    putpixel(img, xc + x, yc + y, c);
    putpixel(img, xc - x, yc + y, c);
    putpixel(img, xc + x, yc - y, c);
    putpixel(img, xc - x, yc - y, c);
    putpixel(img, xc + y, yc + x, c);
    putpixel(img, xc - y, yc + x, c);
    putpixel(img, xc + y, yc - x, c);
    putpixel(img, xc - y, yc - x, c);
}
 
//Bresenham's circle algorithm
void draw_circle(IMAGE *img, int xc, int yc, int r, int fill, unsigned long c) {
    // (xc, yc) 为圆心，r 为半径
    // fill 为是否填充
    // c 为颜色值
 
    // 如果圆在图片可见区域外，直接退出
    if (xc + r < 0 || xc - r >= img->w ||
            yc + r < 0 || yc - r >= img->h) return;
 
    int x = 0, y = r, yi, d;
    d = 3 - 2 * r;
 
    if (fill) {
        // 如果填充（画实心圆）
        while (x <= y) {
            for (yi = x; yi <= y; yi ++)
                _draw_circle_8(img, xc, yc, x, yi, c);
 
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y --;
            }
            x++;
        }
    } else {
        // 如果不填充（画空心圆）
        while (x <= y) {
            _draw_circle_8(img, xc, yc, x, y, c);
 
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y --;
            }
            x ++;
        }
    }
}
//圆弧 