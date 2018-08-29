/*
 * 获取游戏等级信息
 * 解析按钮字符串
 * 字符串转小写
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "game.h"
#include "game_input.h"
#include "game_output.h"

//读入数据，并返回存储好数据的game结构指针，方便查阅
struct GameStruct* getGameLevelInfo()
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
    Game.buttons = (Button *)malloc(sizeof(Button) * Game.buttonNum);  //注意，将在gameover时free！！

    char buttonStr[BUTTON_STR_MAX_LENGTH];
    printf("请输入按钮信息(空格分隔)：");
    for (int i = 0; i < Game.buttonNum; i++)
    {
        scanf("%s", buttonStr);
        Game.buttons[i] = analyseButtonStr(buttonStr);
    }
    printButtons(Game.buttons, Game.buttonNum);
    return &Game;
}

//将传入的按钮字符串解析为按钮结构
Button analyseButtonStr(char *buttonStr)
{
    Button tempButton = {.type = UNKNOW, .number = {0}};
    //解析按钮是不是加减乘除
    switch (buttonStr[0])
    {
    case '+':
        tempButton.type = PLUS;
        sscanf(buttonStr, "+%d\n", tempButton.number);
        break;
    case '-':
        tempButton.type = MINUS;
        sscanf(buttonStr, "-%d", tempButton.number);
        break;
    case '*':
        tempButton.type = MULTIPLY;
        sscanf(buttonStr, "*%d", tempButton.number);
        break;
    case '/':
        tempButton.type = DIVIDE;
        sscanf(buttonStr, "/%d", tempButton.number);
        break;
    case '<':
        tempButton.type = BACKSPACE;
        break;
    }
    if (strstr(buttonStr, "=>"))
    {
        tempButton.type = REPLACE;
        sscanf(buttonStr, "%d=>%d", tempButton.number, tempButton.number + 1);
    }
    //隐含条件，先判定不是=》按钮，再判定是不是第一个数字才能确定时追加按钮
    else if (buttonStr[0] >= '0' && buttonStr[0] <= '9')
    {
        tempButton.type = APPEND;
        sscanf(buttonStr, "%d", tempButton.number);
    }
    else if (strstr(buttonStr, "x^"))
    {
        tempButton.type = POW;
        sscanf(buttonStr, "x^%d", tempButton.number);
    }
    else if (strstr(buttonStr, "+/-"))
    {
        tempButton.type = SIGN_CONVERT;
    }
    else if (!strcmp(strlwr(buttonStr), "reverse") || !strcmp(strlwr(buttonStr), "r"))
    {
        tempButton.type = REVERSE;
    }
    else if ( strstr(strlwr(buttonStr), "shift") )
    {
        tempButton.type = SHIFT;
        //用操作数存储左移和或右移的信息
        *tempButton.number = strstr(buttonStr, ">") ? '>' : strstr(buttonStr, "<") ? '<' : '?' ;
    }
	else if ( !strcmp(strlwr(buttonStr), "mirror") )
	{
		tempButton.type = MIRROR;
	}
    else if ( !strcmp(strlwr(buttonStr), "sum") )
    {
        tempButton.type = SUM;
    }
    else if ( !strcmp(strlwr(buttonStr), "store") )
    {
        tempButton.type = STORE;
    }
    else if (buttonStr[0]=='[' && buttonStr[2]==']')
    {
        tempButton.type = MODIFY;
        tempButton.number[0] = buttonStr[1];  //存储操作符
        sscanf(buttonStr+3, "%d", tempButton.number+1);  //存储操作数
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
