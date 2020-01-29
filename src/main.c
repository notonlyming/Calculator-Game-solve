/*
 * 这是一个用来计算一个叫Calculator游戏的小程序
 * Calculator是一个萌萌的计算器游戏
 * 通过限定次数，和用指定的按键来得到最终的结果
 * 程序通过穷尽所有的组合来得到结果
 * Code by LittleMing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_input.h"
#include "game_process.h"
#include "game_output.h"
#include "game.h"
#include "stepObserver.h"

int main(int argc, char **argv) {
    #ifdef WINVER
    system("chcp 65001");
    #endif
    short isOutputSteps = (argc == 2 && !strcmp(argv[1], "showSteps"));
    if (argc == 1 || isOutputSteps) {
        unsigned int counter[2] = {0};
        clock_t startTime;
        struct GameStruct *gameP;
        printWelcome();
        char isContinue;
        do {
            puts("-------------------新的一关开始啦-------------------");
            int achieveCount;
            int* achieveNumbers = getGameAchieve(&achieveCount);
            gameP = getGameLevelInfo();
            for (int i=0; i < achieveCount; i++)
            {
            printf("-----------------------%d-----------------------\n", achieveNumbers[i]);
                gameP->gameAchieve = achieveNumbers[i];
                startTime = clock();
                solveIt(counter, isOutputSteps);
                printSolutionInfo(counter, gameP);
            }
            free(achieveNumbers);
            gameOver();
            printf("Finish task in %lfs.\n", (clock() - startTime) / (double) CLOCKS_PER_SEC);
            puts("---------------------------------------------------");
            printf("Continue?(y/n):");
            do {
                //循环读入，直到得到有效值
            } while ((isContinue = (char) getchar()) != 'y' && isContinue != 'n');
            getchar();  //拿掉换行符
        } while (isContinue != 'n');
    } else if (argc == 2 && !strcmp(argv[1], "debug")) {
        puts("请注意，这是一个程序计算过程观察测试程序！\n只允许使用一个目标！");
        puts("-------------------Debug模式已开启-------------------");
        int achieveCount;
        int* achieveNumbers = getGameAchieve(&achieveCount);
        getGameLevelInfo();
        Game.gameAchieve = achieveNumbers[0];
        pressButtonStepByStep();
        gameOver();
    } else {
        fprintf(stderr, "Error arguments!\n");
    }
    return 0;
}
