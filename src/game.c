/*
 * 该文件用于控制游戏的开始和结束工作，并提供游戏相关信息
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

struct GameStruct Game = {.isOnError = FALSE, .unchangedButtons=NULL,
        .isButtonModify=FALSE, .storeOrNotAnswerStructP=NULL,
        .portalPointer=NULL};

//该函数用于取得按钮对应信息的字符串
char *buttonStr(Button button) {
    static char infoStr[BUTTON_STR_MAX_LENGTH];
    switch (button.type) {
        case PLUS:
            sprintf(infoStr, "＋%d", button.attachedInfo.operationNum);
            break;
        case MINUS:
            sprintf(infoStr, "－%d", button.attachedInfo.operationNum);
            break;
        case MULTIPLY:
            sprintf(infoStr, "×%d", button.attachedInfo.operationNum);
            break;
        case DIVIDE:
            sprintf(infoStr, "÷%d", button.attachedInfo.operationNum);
            break;
        case BACKSPACE:
            strcpy(infoStr, "<<");
            break;
        case APPEND:
            sprintf(infoStr, "%d", button.attachedInfo.appendNum);
            break;
        case REPLACE:
            sprintf(infoStr, "%s=>%s", button.attachedInfo.replaceInfo.strReplaceFrom,
                    button.attachedInfo.replaceInfo.strReplaceTo);
            break;
        case POW:
            sprintf(infoStr, "x^%d", button.attachedInfo.exponent);
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
            sprintf(infoStr, "Shift%c", button.attachedInfo.shiftDirection == SHIFT_RIGHT ? '>' : '<');
            break;
        case MODIFY:
            sprintf(infoStr, "[%c]%d", button.attachedInfo.modifyInfo.arithmeticSymbol,
                    button.attachedInfo.modifyInfo.operationNum);
            break;
        case STORE:
            if (button.attachedInfo.storeNum != STORE_NOTHING)
                sprintf(infoStr, "%d", button.attachedInfo.storeNum);
            else
                strcpy(infoStr, "Store");
            break;
        case LNV10:
            strcpy(infoStr, "lnv10");
            break;
        case SORT:
            sprintf(infoStr, "Sort%c", button.attachedInfo.sortType == SORT_ASCENDING ? '>' : '<');
            break;
        case CUT:
            sprintf(infoStr, "CUT%s", button.attachedInfo.cutNum);
            break;
        case UNKNOW:
            strcpy(infoStr, "UNKNOW");
            break;
    }
    return infoStr;
}

//释放malloc来用来存储一波按钮的空间，以便复用
void gameOver() {
    free(Game.buttons); //有借有还
    free(Game.unchangedButtons);
    freeStoreWayList();
    free(Game.portalPointer);
    Game.buttons = NULL;
    Game.unchangedButtons = NULL;
    Game.portalPointer = NULL;
}

void freeStoreWayList() {
    if (Game.storeOrNotAnswerStructP) {
        free(Game.storeOrNotAnswerStructP->isStoreAnswer);  //释放存储方案数组
        free(Game.storeOrNotAnswerStructP);
        Game.storeOrNotAnswerStructP = NULL;
    }
}

void resetButton() {
    if (Game.isButtonModify == TRUE) {
        for (int i = 0; i < Game.buttonNum; i++) {
            Game.buttons[i] = Game.unchangedButtons[i];
        }
        Game.isButtonModify = FALSE;
    }
}

void backupButton() {
    Game.isButtonModify = TRUE;
    if (Game.unchangedButtons == NULL) {
        Game.unchangedButtons = (Button *) malloc(sizeof(Button) * Game.buttonNum);
    }
    for (int i = 0; i < Game.buttonNum; i++) {
        Game.unchangedButtons[i] = Game.buttons[i];
    }
}