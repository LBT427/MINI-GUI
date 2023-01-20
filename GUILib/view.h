/*** 
 * @Author: liubotao
 * @Date: 2023-01-20 17:19:07
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-21 02:53:40
 * @FilePath: \MINI-GUI\GUILib\view.h
 * @Description: 
 * @
 */
#ifndef __VIEWS_H__
#define __VIEWS_H__


#include "libConfig.h"
#include "widget.h"

struct View_Methods_t;

#define MAXwidgetsNum 10
#define MAXviewName 20


typedef struct 
{
    char viewName[MAXviewName]; //����
    
    uint16_t viewX; //λ��
    uint16_t viewY;

    uint16_t width; //��С
    uint16_t height;

    int8_t viewPriority;   //��ʾ���ȼ� ԽСԽ����

    uint8_t *viewBuffer;    //�Դ�
    uint16_t bufferSize;    //�Դ��С

    struct View_Methods_t * ViewMethods;    //��Ա����
    OLED_t * screen;                        //��ĻӲ��
    Widget_t *Widgets[MAXwidgetsNum];       //���

}View_t;

struct View_Methods_t
{
    void (*viewDestructor)(View_t *const this);//������������
    void (*viewSetStart)(View_t *const this, uint8_t x, uint8_t y);//���ô���λ��
    void (*viewSetSize)(View_t *const this, uint8_t x, uint8_t y);//���ô��ڴ�С(ͬʱ�������ڻ��棿)
    void (*viewDisplaySwitch)(View_t *const this, int8_t viewPriority);//���ô�����ʾ���ȼ� ԽСԽ����
    void (*viewRefreshBuffer)(View_t *const this);//ˢ�´��ڵ���Ļ�Դ�
    void (*viewClearReverse)(View_t *const this);//�����������

};

void viewDestructor(View_t *const this);                            // ������������
void viewSetStart(View_t *const this, uint8_t x, uint8_t y);        // ���ô���λ��
void viewSetSize(View_t *const this, uint8_t x, uint8_t y);         // ���ô��ڴ�С(ͬʱ�������ڻ��棿)
void viewDisplaySwitch(View_t *const this, int8_t viewPriority);    // ���ô����Ƿ���ʾ
void viewRefreshBuffer(View_t *const this);                         // ���ô�����ʾ���ȼ� ԽСԽ����
void viewClearReverse(View_t *const this);                          // �����������

uint8_t viewConstructor(OLED_t *const screen, View_t *const view,
                        uint16_t width, uint16_t height,
                        uint16_t viewX, uint16_t viewY,
                        uint8_t *viewBuffer, int8_t priority,
                        char name[20]);

#define MAXviewNum 10

struct viewScheduler_t
{
    uint16_t viewClock; //����ʱ ����0�Ǵ��� �����¼�
    View_t *viewID[MAXviewNum];
    uint8_t viewNUM;
};

#endif
