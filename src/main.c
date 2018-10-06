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
#include <string.h>
#include <time.h>
#include "game_input.h"
#include "game_process.h"
#include "game_output.h"
#include "game.h"
#include "stepObserver.h"

int main(int argc, char **argv)
{
    short isOutputSteps = ( argc == 2 && !strcmp(argv[1], "showSteps") );
    if ( argc == 1 || isOutputSteps )
    {
        unsigned int counter[2] = {0};
        clock_t startTime;
        struct GameStruct *gameP;
        printWelcome();
        char isContinue;
        do
        {
            puts("-------------------新的一关开始啦-------------------");
            gameP = getGameLevelInfo();
            startTime = clock();
            solveIt(counter , isOutputSteps);
            gameOver();
            printSolutionInfo(counter, gameP);
            printf("Finish task in %lfs.\n", (clock() - startTime) / (double)CLOCKS_PER_SEC);
            printf("Continue?(y/n):");
            do {
                ;
            }while ( (isContinue = (char) getchar()) == '\n' );
        } while (isContinue != 'n');
    }
    else if ( argc == 2 && !strcmp(argv[1], "debug") )
    {
        puts("请注意，这是一个程序计算过程观察测试程序！");
        puts("-------------------Debug模式已开启-------------------");
        getGameLevelInfo();
        pressButtonStepByStep();
        gameOver();
    }
    else
    {
        fprintf(stderr, "Error arguments!\n");
    }
    return 0;
}