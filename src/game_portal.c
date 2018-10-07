/*
 * 处理传送门的代码
 */

#include "game_portal.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int checkPortalStatus(portal portalToCheck, int currentNumber) {
    int status;
    if (currentNumber / (int) pow(10, portalToCheck.portalEntranceIndex - 1) > 0) {
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
        int numberOnEntrance = result / (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1) % 10;
        int numberToAdd = ((result -
                            //除去传送区域左边的数值
                            (result / (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1) *
                             (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1)))) /
                          //除去传送区域右边的数值
                          (int) pow(10, portalToDoTransmit.portalExitIndex - 1);
        result = result / (int) pow(10, portalToDoTransmit.portalEntranceIndex) *
                 (int) pow(10, portalToDoTransmit.portalEntranceIndex - 1) +  //传送区域左端的数值
                 //传送区域中间的已传送数值
                 (numberToAdd + numberOnEntrance) * (int) pow(10, portalToDoTransmit.portalExitIndex - 1) +
                 (portalToDoTransmit.portalExitIndex > 1 ?
                  result % (int) pow(10, portalToDoTransmit.portalExitIndex - 1)
                                                         : 0);  //传送区域右边的数值
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
    getchar();  //拿掉换行符
}