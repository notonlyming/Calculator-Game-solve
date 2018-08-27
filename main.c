/*
 * 这是一个用来计算一个叫Calculator游戏的小程序
 * Calculator是一个萌萌的计算器游戏
 * 通过限定次数，和用指定的按键来得到最终的结果
 * 这是一个数学游戏
 * 程序通过穷尽所有的组合来得到结果
 * Code by LittleMing
 * Updated 2018.8.27
 */

#include <stdio.h>
#include "game_input.h"
#include "game_process.h"

int main(void)
{
    do
    {
        getGameLevelInfo();
        solveIt();
        puts("温馨提示：退出请按Ctrl+C");
        puts("-----------------新的一关开始啦-----------------");
    } while (1);
    return 0;
}