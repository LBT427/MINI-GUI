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
    char viewName[MAXviewName]; //名字
    
    uint16_t viewX; //位置
    uint16_t viewY;

    uint16_t width; //大小
    uint16_t height;

    int8_t viewPriority;   //显示优先级 越小越靠上

    uint8_t *viewBuffer;    //显存
    uint16_t bufferSize;    //显存大小

    struct View_Methods_t * ViewMethods;    //成员函数
    OLED_t * screen;                        //屏幕硬件
    Widget_t *Widgets[MAXwidgetsNum];       //组件

}View_t;

struct View_Methods_t
{
    void (*viewDestructor)(View_t *const this);//窗口析构函数
    void (*viewSetStart)(View_t *const this, uint8_t x, uint8_t y);//设置窗口位置
    void (*viewSetSize)(View_t *const this, uint8_t x, uint8_t y);//设置窗口大小(同时调整窗口缓存？)
    void (*viewDisplaySwitch)(View_t *const this, int8_t viewPriority);//设置窗口显示优先级 越小越靠上
    void (*viewRefreshBuffer)(View_t *const this);//刷新窗口到屏幕显存
    void (*viewClearReverse)(View_t *const this);//清除窗口内容

};

void viewDestructor(View_t *const this);                            // 窗口析构函数
void viewSetStart(View_t *const this, uint8_t x, uint8_t y);        // 设置窗口位置
void viewSetSize(View_t *const this, uint8_t x, uint8_t y);         // 设置窗口大小(同时调整窗口缓存？)
void viewDisplaySwitch(View_t *const this, int8_t viewPriority);    // 设置窗口是否显示
void viewRefreshBuffer(View_t *const this);                         // 设置窗口显示优先级 越小越靠上
void viewClearReverse(View_t *const this);                          // 清除窗口内容

uint8_t viewConstructor(OLED_t *const screen, View_t *const view,
                        uint16_t width, uint16_t height,
                        uint16_t viewX, uint16_t viewY,
                        uint8_t *viewBuffer, int8_t priority,
                        char name[20]);

#define MAXviewNum 10

struct viewScheduler_t
{
    uint16_t viewClock; //倒计时 减到0是触发 更新事件
    View_t *viewID[MAXviewNum];
    uint8_t viewNUM;
};

#endif
