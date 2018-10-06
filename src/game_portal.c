/*
 * 处理传送门的代码
 * Created by lm on 18-10-6.
 */

#include "game_portal.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int checkPortalStatus(portal portalToCheck, int currentNumber) {
    int status;
    //printf("c/p = %d", currentNumber / (int)pow(10, portalToCheck.portalEntranceIndex - 1));
    if (currentNumber / (int)pow(10, portalToCheck.portalEntranceIndex - 1) > 0) {
        status = PORTAL_HAS_NUMBER;
    } else {
        status = PORTAL_NO_NUMBER;
    }
    return status;
}

int doTransmit(portal portalToDoTransmit, int currentNumber) {
    short sign = (short) (currentNumber >= 0 ? +1 : -1);
    int result = currentNumber < 0 ? -currentNumber : currentNumber;
    while (checkPortalStatus(portalToDoTransmit, result) == PORTAL_HAS_NUMBER) {
        //printf("需要传送！ 当前数值：%d ", result);
        int numberOnEntrance = result / (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1) % 10;
        int numberToAdd = (result - (result / (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1) *
                                     (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1))) -
                          result % (int) pow(10, portalToDoTransmit.portalExitIndex - 1);
        result = (result / (int) pow(10, portalToDoTransmit.portalExitIndex - 1) / 10 *
                  (int) pow(10, portalToDoTransmit.portalExitIndex - 2)) +
                 numberToAdd + numberOnEntrance;
        //printf("欲传送数值：%d 传送目的地：%d 传送后：%d\n", numberOnEntrance, numberToAdd, result);
    }
    return result * sign;
}

void getAndInitialisePortal() {
    printf("有传送门吗？（y/n）");
    if (getchar() == 'y') {
        if (Game.portalPointer == NULL) {
            Game.portalPointer = (portal *) malloc(sizeof(portal));
        }
        printf("请输入传送门传送入口和传送出口位置（空格分隔）：");
        scanf("%d%d", &Game.portalPointer->portalEntranceIndex, &Game.portalPointer->portalExitIndex);
    }

}