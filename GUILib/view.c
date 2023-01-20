/*
 * @Author: liubotao
 * @Date: 2023-01-20 17:18:57
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-21 03:10:36
 * @FilePath: \MINI-GUI\GUILib\view.c
 * @Description:
 *
 */
#include "view.h"
#include <string.h>

struct viewScheduler_t viewScheduler;
struct View_Methods_t ViewMethods;

#define ViewERROR   1
#define ViewOK      0
uint8_t viewConstructor(OLED_t *const screen, View_t *const view,
                        uint16_t width, uint16_t height,
                        uint16_t viewX, uint16_t viewY,
                        uint8_t *viewBuffer, int8_t priority,
                        char name[20])
{

    if(screen==NULL)return ViewERROR;
    if(view==NULL)return ViewERROR;
    if (width > screen->width && height > screen->height)return ViewERROR;
    if (viewX > screen->width && viewY > screen->height)return ViewERROR;

    ViewMethods.viewDestructor = viewDestructor;
    ViewMethods.viewSetStart = viewSetStart;
    ViewMethods.viewSetSize = viewSetSize;
    ViewMethods.viewDisplaySwitch = viewDisplaySwitch;
    ViewMethods.viewRefreshBuffer = viewRefreshBuffer;
    ViewMethods.viewClearReverse = viewClearReverse;

    view->ViewMethods = &ViewMethods;
    strcpy(view->viewName, name);
    view->screen = screen;
    view->viewX = viewX;
    view->viewY = viewY;

    view->width = width;
    view->height = height;

    view->viewBuffer = viewBuffer;
    view->bufferSize = width * height;

    if (priority>MAXviewNum)return ViewERROR;
    
    viewScheduler.viewID[priority] = view;
    viewScheduler.viewNUM++;
    return ViewOK;
}

void viewDestructor(View_t *const this) // ������������
{
}
void viewSetStart(View_t *const this, uint8_t x, uint8_t y) // ���ô���λ��
{
    this->viewX = x;
    this->viewY = y;
}
void viewSetSize(View_t *const this, uint8_t x, uint8_t y) // ���ô��ڴ�С(ͬʱ�������ڻ��棿)
{
    this->width = x;
    this->height = y;
}
void viewDisplaySwitch(View_t *const this, int8_t viewPriority) // ���ô������ȼ�1���0��ʹ�� -1����
{
    this->viewPriority = viewPriority;
}
void viewRefreshBuffer(View_t *const this) // ˢ�´��ڵ���Ļ�Դ� �����ݸ��Ƶ���ʾ�������� ����ˢ�¿���ֱ���滻�Դ�ָ��
{
    if (!this->screen->idleBuffer)                      //Ԥ����
    {
        this->screen->oledBuffer2 = this->viewBuffer;//??
        this->screen->idleBuffer = 1;
    }
    else
    {
        this->screen->oledBuffer1 = this->viewBuffer;
        this->screen->idleBuffer = 0;
    }
}
void viewClearReverse(View_t *const this) // �����������
{
    memset(this->viewBuffer, 0x00, this->bufferSize);
}

void viewSchedulerRefresh()
{
    if (viewScheduler.viewClock > 0)
        return;
    if (viewScheduler.viewNUM == 0)
        return;
    for (uint8_t i = MAXviewNum; i < 0; i--)//Ĭ��˳��������ʾ �������ȼ�1��� -1����
    {

        int8_t priority = viewScheduler.viewID[i]->viewPriority;
        if (priority == -1) //�������ȼ�Ϊ-1ʱ��ˢ��
            continue;
        if (priority == 0)  // ˢ�� ʱ��ˢ�µ͵ģ���ײ㣩 ��Ĭ�ϵģ��м䣩 ���ߵģ��������棩
            viewScheduler.viewID[i]->ViewMethods->viewRefreshBuffer;
        else

    }

}
