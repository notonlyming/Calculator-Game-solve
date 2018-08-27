/*
 * 获取游戏等级信息
 * 解析按钮字符串
 * 字符串转小写
 */

#ifndef _STDIO_H_
#define _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _CTYPE_H_
#define _CTYPE_H_
#include <ctype.h>
#endif

#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#endif

#ifndef _GAME_H_
#define _GAME_H_
#include "game.h"
#endif

#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_
#include "game_input.h"
#endif

#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include "game_output.h"
#endif

void getGameLevelInfo()
{
    printf("请输入计算器起始的数值：");
    scanf("%d", &(Game.startNum));

    printf("请输入允许的最大步数：");
    scanf("%d", &(Game.allowMaxStep));

    printf("请输入游戏目标：");
    scanf("%d", &(Game.gameAchieve));

    printf("请输入有多少个按钮：");
    scanf("%d", &(Game.buttonNum));
    getchar(); //拿掉换行符
    Game.buttons = (Button *)malloc(sizeof(Button) * Game.buttonNum);

    char buttonStr[BUTTON_STR_MAX_LENGTH];
    for (int i = 0; i < Game.buttonNum; i++)
    {
        printf("请输入按钮信息(操作符和数字)：");
        fgets(buttonStr, sizeof(buttonStr), stdin);
        buttonStr[strlen(buttonStr) - 1] = '\0'; //去掉fgets读取的换行符
        Game.buttons[i] = analyseButtonStr(buttonStr);
        printButtons(Game.buttons, i + 1);
    }
}

//将传入的按钮字符串解析为按钮结构
Button analyseButtonStr(char *buttonStr)
{
    Button tempButton = {.type = UNKNOW, .number = NULL};
    //解析按钮是不是加减乘除
    switch (buttonStr[0])
    {
    case '+':
        tempButton.type = PLUS;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "+%d\n", tempButton.number);
        break;
    case '-':
        tempButton.type = MINUS;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "-%d", tempButton.number);
        break;
    case '*':
        tempButton.type = MULTIPLY;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "*%d", tempButton.number);
        break;
    case '/':
        tempButton.type = DIVIDE;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "/%d", tempButton.number);
        break;
    case '<':
        tempButton.type = BACKSPACE;
        tempButton.number = NULL;
        break;
    }
    if (strstr(buttonStr, "=>"))
    {
        tempButton.type = REPLACE;
        tempButton.number = (int *)malloc(sizeof(int) * 2);
        sscanf(buttonStr, "%d=>%d", tempButton.number, tempButton.number + 1);
    }
    //隐含条件，先判定不是=》按钮，再判定是不是第一个数字才能确定时追加按钮
    else if (buttonStr[0] >= '0' && buttonStr[0] <= '9')
    {
        tempButton.type = APPEND;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "%d", tempButton.number);
    }
    else if (strstr(buttonStr, "x^2"))
    {
        tempButton.type = SQUARE;
        tempButton.number = NULL;
    }
    else if (strstr(buttonStr, "+/-"))
    {
        tempButton.type = SIGN_CONVERT;
        tempButton.number = NULL;
    }
    else if (!strcmp(strlwr(buttonStr), "reverse") || !strcmp(strlwr(buttonStr), "r"))
    {
        tempButton.type = REVERSE;
        tempButton.number = NULL;
    }
    if (tempButton.type == UNKNOW)
    {
        fprintf(stderr, "啊啊啊，您输入了无法识别的按钮信息~\n程序将退出！\n");
        exit(1);
    }
    return tempButton;
}

//字符串转小写函数
char *strlwr(char *str)
{
    if (str == NULL)
        return NULL;
    char *p = str;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
            *p = (*p) + 0x20;
        p++;
    }
    return str;
}