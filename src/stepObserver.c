#include <stdio.h>
#include "game.h"
#include "game_process.h"
#include "game_output.h"

void pressButtonStepByStep()
{
    int buttonIndex;
    int result = Game.startNum;
    for (int i = 0; i < Game.allowMaxStep; i++)
    {
        printf("输入按钮编号：");
        scanf("%d", &buttonIndex);
        printf("按下按钮：【%s】\n", buttonStr(Game.buttons[buttonIndex]));
        if (Game.buttons[buttonIndex].type == MODIFY)
        {
            pressButton(Game.buttons[buttonIndex], result);
            printButtons(Game.buttons, Game.buttonNum);
        }
        else if (Game.buttons[buttonIndex].type == STORE)
        {
            short choose;
            printf("Enter your choose [1.store 2.append]:");
            scanf("%hi", &choose);
            if (choose == 1)
            {
                storeNumberToButton(result, &Game.buttons[buttonIndex]);
                printf("Stored %d\n", Game.buttons[buttonIndex].attachedInfo.storeNum);
                i--;
            }
            else if (choose == 2)
            {
                goto normalButtonPress;
            }
            else
            {
                fprintf(stderr, "You enter a invalid value!\n");
            }
        }
        else
        {
            normalButtonPress:
            printf("%d -> ", result);
            result = pressButton(Game.buttons[buttonIndex], result);
            printf("%d status:%s\n", result, Game.isOnError ? "ERROR" : "OK");
        }
        puts("-----------------------------------------------------");
    }
}

void printSteps(unsigned short answer[], storeOrNotAnswerNode *storeAnswerList)
{
    printf("当前解决方案 普通：");
    for (int i = 0; i < Game.allowMaxStep; ++i) {
        printf("%d", answer[i]);
    }
    if (storeAnswerList)
    {
        printf(" 存储：");
        for (int j = 0; j < Game.allowMaxStep; ++j) {
            printf("%d", storeAnswerList->isStoreAnswer[j]);
        }
    }

    putchar('\n');
}