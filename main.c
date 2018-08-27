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
    unsigned int counter[2] = {0};
    struct GameStruct *gameP;
    do
    {
        gameP = getGameLevelInfo();
        solveIt(counter);
        gameOver();
        if (counter[1] == 0)
        {
            fprintf(stderr,
                    "我们做了%d次尝试，还是无法找到任何解。\n请检查输入是否有误，如果确认无误且有解，请在Github提issue。\n",
                    counter[0]);
            printf("note:\n  start:%d steps:%d achieve:%d Buttons:%d\n",
            gameP->startNum, gameP->allowMaxStep, gameP->gameAchieve, gameP->buttonNum);
        }
        else
        {
            printf("\nnote: %d times try, %d solutions found\n", counter[0], counter[1]);
        }
        puts("温馨提示：退出请按Ctrl+C");
        puts("----------------新的一关开始啦----------------");
    } while (1);
    return 0;
}