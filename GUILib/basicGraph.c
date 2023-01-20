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


//����:�����Ļ��������
void ClearScreenBuffer(unsigned char val)
{
  memset(ScreenBuffer, val, sizeof(ScreenBuffer));
}



//��
//���õ�ǰѡ��Ļ����� �� ĳһ���������
void SetPointBuffer(int x, int y, int value)
{
  if (x > SCREEN_COLUMN - 1 || y > SCREEN_ROW - 1) //������Χ
    return;

  if (value)
    ScreenBuffer[y / SCREEN_PAGE_NUM][x] |= 1 << (y % SCREEN_PAGE_NUM);
  else
    ScreenBuffer[y / SCREEN_PAGE_NUM][x] &= ~(1 << (y % SCREEN_PAGE_NUM));
}

//��

// �������� a ��b ��ֵ
inline void swap_int(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
 
// Bresenham's line algorithm
void draw_line(IMAGE *img, int x1, int y1, int x2, int y2, unsigned long c) {
    // ���� c Ϊ��ɫֵ
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
 
    if (yy) { // ���ֱ���� x ��ļнǴ��� 45 ��
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
    } else { // ���ֱ���� x ��ļн�С�� 45 ��
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

//�� 
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD_WR_DATA(color[i*width+j]);//д������ 
	}	  
} 

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//���� 
//����� 



//Բ 
// �˶Գ���
inline void _draw_circle_8(IMAGE *img, int xc, int yc, int x, int y, unsigned long c) {
    // ���� c Ϊ��ɫֵ
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
    // (xc, yc) ΪԲ�ģ�r Ϊ�뾶
    // fill Ϊ�Ƿ����
    // c Ϊ��ɫֵ
 
    // ���Բ��ͼƬ�ɼ������⣬ֱ���˳�
    if (xc + r < 0 || xc - r >= img->w ||
            yc + r < 0 || yc - r >= img->h) return;
 
    int x = 0, y = r, yi, d;
    d = 3 - 2 * r;
 
    if (fill) {
        // �����䣨��ʵ��Բ��
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
        // �������䣨������Բ��
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
//Բ�� 