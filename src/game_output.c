/*
 * 该文件用于实现程序的输出功能
 */

#include <stdio.h>
#include "game.h"
#include "game_output.h"
#include "game_process.h"

void printButtons(Button buttons[], int buttonNumber) {
    puts("--------------------当前已有按钮--------------------");
    for (int i = 0; i < buttonNumber; i++) {
        printf("%d.【%s】 ", i, buttonStr(buttons[i]));
        //每五个一换行,且不是最后一行
        if ((i + 1) % 5 == 0 && (i + 1) != buttonNumber) {
            putchar('\n');
        }
    }
    putchar('\n');
}

//打印结果统计信息
void printSolutionInfo(unsigned int counter[2], struct GameStruct *gameP) {
    if (counter[1] == 0) {
        fprintf(stderr,
                "我们做了%d次尝试，还是无法找到任何解。\n请检查输入是否有误，如果确认无误且有解，请在Github提issue。\n",
                counter[0]);
        printf("note:\n  start:%d steps:%d achieve:%d Buttons:%d\n",
               gameP->startNum, gameP->allowMaxStep, gameP->gameAchieve, gameP->buttonNum);
    } else {
        printf("\nnote: %d time(s) try, %d solution(s) found\n", counter[0], counter[1]);
    }
}

void printWelcome() {
    puts("+-+-+-+-+-+-+-+-+-+-+");
    puts("|C|a|l|c|u|l|a|t|o|r|");
    puts("+-+-+-+-+-+-+-+-+-+-+");
    puts("----------------------------------------------------");
    puts("Welcome to solution calculator of calculator game!");
    puts("项目已在GitHub开源，欢迎各位大佬提出宝贵意见。");
    puts("https://github.com/notonlyming/Calculator-Game-solve");
}

void printSolution(unsigned short answer[], int stepsNum) {
    resetButton();
    int tempResult = Game.startNum;
    printf("发现解(%d步)：", stepsNum);
    //打印解
    for (int step = 0; step < stepsNum; step++) {
        if (Game.storeOrNotAnswerStructP) {
            if (Game.storeOrNotAnswerStructP->isStoreAnswer[step]) {
                storeNumberToButton(tempResult, Game.storeOrNotAnswerStructP->storeButtonP);
                printf("(Store) ");
            }
        }
        tempResult = pressButton(Game.buttons[answer[step]], tempResult);
        printf("(%s) ", buttonStr(Game.buttons[answer[step]]));
    }
    printf("结果：%d\n", tempResult);
}