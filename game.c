/*
 * 按钮枚举类型
 * 按钮结构
 * 游戏结构
 * 获取按钮字符串
 */

#ifndef _STDIO_H_
#define _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#endif

#ifndef _GAME_H_
#define _GAME_H_
#include "game.h"
#endif

struct GameStruct Game = {.isOnError = FALSE};

//该函数用于取得按钮对应信息的字符串
char *buttonStr(Button button)
{
    static char infoStr[BUTTON_STR_MAX_LENGTH];
    switch (button.type)
    {
    case PLUS:
        sprintf(infoStr, "＋%d", *(button.number));
        break;
    case MINUS:
        sprintf(infoStr, "－%d", *(button.number));
        break;
    case MULTIPLY:
        sprintf(infoStr, "×%d", *(button.number));
        break;
    case DIVIDE:
        sprintf(infoStr, "÷%d", *(button.number));
        break;
    case BACKSPACE:
        strcpy(infoStr, "<<");
        break;
    case APPEND:
        sprintf(infoStr, "%d", *(button.number));
        break;
    case REPLACE:
        sprintf(infoStr, "%d=>%d", button.number[0], button.number[1]);
        break;
    case POW:
        sprintf(infoStr, "x^%d", *(button.number) );
        break;
    case SIGN_CONVERT:
        strcpy(infoStr, "+/-");
        break;
    case REVERSE:
        strcpy(infoStr, "Reverse");
        break;
    case SUM:
        strcpy(infoStr, "SUM");
        break;
    case SHIFT:
        sprintf(infoStr, "Shift%c", *(button.number) );
        break;
    case UNKNOW:
        strcpy(infoStr, "UNKNOW");
        break;
    }
    return infoStr;
}

//释放malloc来用来存储一波按钮的空间，以便复用
void gameOver()
{
    free(Game.buttons); //有借有还
}