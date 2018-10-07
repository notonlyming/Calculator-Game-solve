/*
 * 该文件用于实现程序的输入功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_input.h"
#include "game_output.h"

//读入数据，并返回存储好数据的game结构指针，方便查阅
struct GameStruct *getGameLevelInfo() {
    printf("请输入计算器起始的数值：");
    scanf("%d", &(Game.startNum));

    printf("请输入允许的最大步数：");
    scanf("%hu", &(Game.allowMaxStep));

    printf("请输入游戏目标：");
    scanf("%d", &(Game.gameAchieve));
    getchar(); //拿掉换行符

    //读入按钮信息字符串
    char buttonAllStr[BUTTON_STR_MAX_LENGTH * MAX_BUTTON_NUM];
    printf("请输入按钮信息(单个空格分隔,回车结束)：");
    fgets(buttonAllStr, BUTTON_STR_MAX_LENGTH * MAX_BUTTON_NUM, stdin);
    buttonAllStr[strlen(buttonAllStr) - 1] = '\0';  //除去末尾的换行符

    //计算按钮个数和申请空间
    Game.buttonNum = (unsigned short) (countBlankNum(buttonAllStr) + 1);
    Game.buttons = (Button *) malloc(sizeof(Button) * Game.buttonNum);  //注意，将在gameOver时free！！

    //将数据写入按钮数组
    char buttonStr[BUTTON_STR_MAX_LENGTH];
    char *strP = buttonAllStr; //字符串指针，指向没有读取的按钮字符串信息的开头
    for (int i = 0; i < Game.buttonNum; i++) {
        sscanf(strP, "%s", buttonStr);
        //移动字符串的指针越过已经读过的字节和开头的空格
        strP = strP + strlen(buttonStr) + 1;
        Game.buttons[i] = analyseButtonStr(buttonStr);
    }
    getAndInitialisePortal();
    printButtons(Game.buttons, Game.buttonNum);
    return &Game;
}

int countBlankNum(char *strToCount) {
    int counter = 0;
    while (strchr(strToCount, ' ')) {
        //后移指针，继续找后面的空格
        strToCount = strchr(strToCount, ' ') + 1;
        counter++;
    }
    return counter;
}

//将传入的按钮字符串解析为按钮结构
Button analyseButtonStr(char *buttonStr) {
    Button tempButton = {.type = UNKNOW};
    //解析按钮是不是加减乘除
    switch (buttonStr[0]) {
        case '+':
            tempButton.type = PLUS;
            sscanf(buttonStr, "+%d\n", &tempButton.attachedInfo.operationNum);
            break;
        case '-':
            tempButton.type = MINUS;
            sscanf(buttonStr, "-%d", &tempButton.attachedInfo.operationNum);
            break;
        case '*':
            tempButton.type = MULTIPLY;
            sscanf(buttonStr, "*%d", &tempButton.attachedInfo.operationNum);
            break;
        case '/':
            tempButton.type = DIVIDE;
            sscanf(buttonStr, "/%d", &tempButton.attachedInfo.operationNum);
            break;
        default:
            break;
    }
    if (strstr(buttonStr, "=>")) {
        tempButton.type = REPLACE;
        sscanf(strstr(buttonStr, "=>") + 2, "%s", tempButton.attachedInfo.replaceInfo.strReplaceTo);
        *strstr(buttonStr, "=>") = '\0';
        sscanf(buttonStr, "%s", tempButton.attachedInfo.replaceInfo.strReplaceFrom);
    }
        //隐含条件，先判定不是=》按钮，再判定是不是第一个数字才能确定时追加按钮
    else if (buttonStr[0] >= '0' && buttonStr[0] <= '9') {
        tempButton.type = APPEND;
        sscanf(buttonStr, "%d", &tempButton.attachedInfo.appendNum);
    } else if (strstr(buttonStr, "x^")) {
        tempButton.type = POW;
        sscanf(buttonStr, "x^%d", &tempButton.attachedInfo.exponent);
    } else if (strstr(buttonStr, "+/-")) {
        tempButton.type = SIGN_CONVERT;
    } else if (!strcmp(strlwr(buttonStr), "reverse")) {
        tempButton.type = REVERSE;
    } else if (strstr(strlwr(buttonStr), "shift")) {
        tempButton.type = SHIFT;
        //用操作数存储左移和或右移的信息
        if (strstr(buttonStr, ">")) {
            tempButton.attachedInfo.shiftDirection = SHIFT_RIGHT;
        } else if (strstr(buttonStr, "<")) {
            tempButton.attachedInfo.shiftDirection = SHIFT_LEFT;
        } else {
            tempButton.type = UNKNOW;
        }
    } else if (!strcmp(strlwr(buttonStr), "mirror")) {
        tempButton.type = MIRROR;
    } else if (!strcmp(strlwr(buttonStr), "sum")) {
        tempButton.type = SUM;
    } else if (!strcmp(strlwr(buttonStr), "store")) {
        tempButton.type = STORE;
        tempButton.attachedInfo.storeNum = STORE_NOTHING;  //存储为-1表示没有存储相应的数字，短按将不能追加
    } else if (buttonStr[0] == '[' && buttonStr[2] == ']') {
        tempButton.type = MODIFY;
        tempButton.attachedInfo.modifyInfo.arithmeticSymbol = buttonStr[1];  //存储操作符
        sscanf(buttonStr + 3, "%d", &tempButton.attachedInfo.modifyInfo.operationNum);  //存储操作数
    } else if (!strcmp(buttonStr, "<<")) {
        tempButton.type = BACKSPACE;
    } else if (!strcmp(strlwr(buttonStr), "lnv10")) {
        tempButton.type = LNV10;
    }
    if (tempButton.type == UNKNOW) {
        fprintf(stderr, "啊啊啊，您输入了无法识别的按钮信息~\n程序将退出！\n");
        exit(1);
    }
    return tempButton;
}

//字符串转小写函数
char *strlwr(char *str) {
    if (str == NULL)
        return NULL;
    char *p = str;
    while (*p != '\0') {
        if (*p >= 'A' && *p <= 'Z')
            *p = (char) ((*p) + 0x20);
        p++;
    }
    return str;
}
