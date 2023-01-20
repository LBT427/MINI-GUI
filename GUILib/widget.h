/*** 
 * @Author: liubotao
 * @Date: 2023-01-20 17:23:32
 * @LastEditors: liubotao
 * @LastEditTime: 2023-01-20 22:23:55
 * @FilePath: \MINI-GUI\GUILib\widget.h
 * @Description: 
 * @
 */
#ifndef __VIDGET_H__
#define __VIDGET_H__

#include "libConfig.h"

typedef struct 
{
    char viewName[20];
    uint8_t viewAdd;

    uint16_t viewX;
    uint16_t viewY;

    uint16_t width;
    uint16_t height;

}Widget_t;


#endif
