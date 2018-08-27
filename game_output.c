/*
 * 打印按钮
 */

#ifndef _STDIO_H_
#define _STDIO_H_
#include <stdio.h>
#endif

#ifndef _GAME_H_
#define _GAME_H_
#include "game.h"
#endif

#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include "game_output.h"
#endif

void printButtons(Button buttons[], int buttonNumber)
{
    printf("-----------------当前已有按钮-----------------\n");
    for (int i = 0; i < buttonNumber; i++)
    {
        printf("按钮%d：【%s】\n", i, buttonStr(buttons[i]));
    }
    printf("---------------------------------------------\n");
}
