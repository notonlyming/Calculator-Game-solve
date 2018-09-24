/*
 * 按钮枚举类型
 * 按钮结构
 * 游戏结构
 * 获取按钮字符串
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

struct GameStruct Game = {.isOnError = FALSE, .unchangeButtons=NULL, .isButtonModify=FALSE, .storeOrNotAnswerListHead=NULL};

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
	case MIRROR:
		strcpy(infoStr, "Mirror");
		break;
    case SUM:
        strcpy(infoStr, "SUM");
        break;
    case SHIFT:
        sprintf(infoStr, "Shift%c", *(button.number) );
        break;
    case MODIFY:
        sprintf(infoStr, "[%c]%d", button.number[0], button.number[1]);
        break;
    case STORE:
        sprintf(infoStr, "%d", *(button.number));
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
    free(Game.unchangeButtons);
    Game.buttons = NULL;
    Game.unchangeButtons = NULL;
}

void resetButton()
{
    if (Game.isButtonModify == TRUE)
    {
        for (int i=0; i<Game.buttonNum; i++)
        {
            Game.buttons[i] = Game.unchangeButtons[i];
        }
        Game.isButtonModify = FALSE;
    }
}

void backupButton()
{
    Game.isButtonModify = TRUE;
    if (Game.unchangeButtons == NULL)
    {
        Game.unchangeButtons = (Button*)malloc(sizeof(Button) * Game.buttonNum);
    }
    for (int i=0; i<Game.buttonNum; i++)
    {
        Game.unchangeButtons[i] = Game.buttons[i];
    }
}