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

void viewDestructor(View_t *const this) // 窗口析构函数
{
}
void viewSetStart(View_t *const this, uint8_t x, uint8_t y) // 设置窗口位置
{
    this->viewX = x;
    this->viewY = y;
}
void viewSetSize(View_t *const this, uint8_t x, uint8_t y) // 设置窗口大小(同时调整窗口缓存？)
{
    this->width = x;
    this->height = y;
}
void viewDisplaySwitch(View_t *const this, int8_t viewPriority) // 设置窗口优先级1最高0不使用 -1隐藏
{
    this->viewPriority = viewPriority;
}
void viewRefreshBuffer(View_t *const this) // 刷新窗口到屏幕显存 把数据复制到显示器缓存里 快速刷新可以直接替换显存指针
{
    if (!this->screen->idleBuffer)                      //预加载
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
void viewClearReverse(View_t *const this) // 清除窗口内容
{
    memset(this->viewBuffer, 0x00, this->bufferSize);
}

void viewSchedulerRefresh()
{
    if (viewScheduler.viewClock > 0)
        return;
    if (viewScheduler.viewNUM == 0)
        return;
    for (uint8_t i = MAXviewNum; i < 0; i--)//默认顺序依次显示 窗口优先级1最高 -1隐藏
    {

        int8_t priority = viewScheduler.viewID[i]->viewPriority;
        if (priority == -1) //窗口优先级为-1时不刷新
            continue;
        if (priority == 0)  // 刷新 时先刷新低的（最底层） 再默认的（中间） 最后高的（再最上面）
            viewScheduler.viewID[i]->ViewMethods->viewRefreshBuffer;
        else

    }

}
