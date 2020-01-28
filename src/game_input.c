/*
 * 该文件用于实现程序的输入功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_input.h"
#include "game_output.h"

// 该函数用于获取游戏目标，因为游戏目标有多个，因此单独一个函数处理
// 返回从用户输入处获得的目标数组(int)，记得free.
// 参数为返回目标数组的元素总数。
int* getGameAchieve(int* achieveCount)
{
    char achieveStr[NUMBER_STR_MAX_LENGTH];
    printf("请输入游戏目标：");
    fgets(achieveStr, NUMBER_STR_MAX_LENGTH, stdin);
    achieveStr[strlen(achieveStr) - 1] = '\0';   //除去末尾的换行符
    
    *achieveCount = countBlankNum(achieveStr, ' ') + 1;
    int* achieveNumbers = (int*)malloc(sizeof(int) * (*achieveCount));  //目标数组
    char** achieveStrs;
    if(*achieveCount > 1){
        achieveStrs = split(achieveStr, " ");
    } else if(*achieveCount == 1 && achieveStr[0] != '\0') {
        achieveStrs = (char**)malloc(sizeof(char**));
        achieveStrs[0] = (char*)malloc(sizeof(char*) * NUMBER_STR_MAX_LENGTH);
        strcpy(achieveStrs[0], achieveStr);
    }else{
        puts("错误的目标字符串！");
        exit(1);
    }
    for (int i=0; i < (*achieveCount); i++)
    {
        sscanf(achieveStrs[i], "%d", &(achieveNumbers[i]));
    }
    // 释放分割字符串数组的内存
    for (int i=0; i < (*achieveCount); i++)
    {
        free(achieveStrs[i]);
    }
    free(achieveStrs);
    return achieveNumbers;    
}


/* 功  能：将str字符串中的oldstr字符串替换为newstr字符串
 * 参  数：str：操作目标 oldstr：被替换者 newstr：替换者
 * 返回值：返回替换之后的字符串
 */
char* strrpc(char *str, char *oldstr, char *newstr){
    char bstr[BUTTON_STR_MAX_LENGTH];//转换缓冲区
    memset(bstr,0,sizeof(bstr));
 
    for(unsigned int i = 0; i < strlen(str); i++) {
        if(!strncmp(str+i, oldstr, strlen(oldstr))){//查找目标字符串
            strcat(bstr, newstr);
            i += strlen(oldstr) - 1;
        } else {
        	strncat(bstr,str + i,1);//保存一字节进缓冲区
	    }
    }
 
    strcpy(str,bstr);
    return str;
}

// 分割字符串。返回的字符串数组在堆上，记得free。
char** split(char* strToSplit, char* splitChar)
{
    int subStrCount = countBlankNum(strToSplit, ' ') + 1;
    char *strP = strToSplit; //字符串指针，指向没有读取的按钮字符串信息的开头
    char *findCharP;
    char** result = (char**)malloc(sizeof(char**) * subStrCount);
    for (int i=0; i < subStrCount; i++)
    {
        findCharP = strstr(strP, splitChar);
        if(findCharP) *findCharP = '\0';
        result[i] = (char*)malloc(sizeof(char*) * MAX_ACHIEVE_NUM);
        strcpy(result[i], strP);
        strP += strlen(result[i]) + 1;
    }
    return result;
}

//读入数据，并返回存储好数据的game结构指针，方便查阅
struct GameStruct *getGameLevelInfo() {
    printf("请输入计算器起始的数值：");
    scanf("%d", &(Game.startNum));

    printf("请输入允许的最大步数：");
    scanf("%hu", &(Game.allowMaxStep));
    getchar();  //拿掉换行符

    //读入按钮信息字符串
    char buttonAllStr[BUTTON_STR_MAX_LENGTH * MAX_BUTTON_NUM];
    printf("请输入按钮信息(单个空格分隔,回车结束)：");
    fgets(buttonAllStr, BUTTON_STR_MAX_LENGTH * MAX_BUTTON_NUM, stdin);
    buttonAllStr[strlen(buttonAllStr) - 1] = '\0';  //除去末尾的换行符
    strlwr(buttonAllStr);   // 全部转换为小写，方便处理
    detectAndInsertDeleteButton(buttonAllStr);

    //计算按钮个数和申请空间
    Game.buttonNum = (unsigned short) (countBlankNum(buttonAllStr, ' ') + 1);
    Game.buttons = (Button *) malloc(sizeof(Button) * Game.buttonNum);  //注意，将在gameOver时free！！

    //将数据写入按钮数组
    char buttonStr[BUTTON_STR_MAX_LENGTH];
    char* strP = buttonAllStr;
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

// 传入用户输入的按钮字符串，如果内含独立的delete则替换为8个独立的delete以实现删除任意位。
void detectAndInsertDeleteButton(char* buttonAllStr)
{
    char* deleteStrStartP = strstr(buttonAllStr, "delete");
    // 如果包含delete字符串，且后边不跟数字，则需要替换！
    if(deleteStrStartP && !isNumberBit(deleteStrStartP + strlen("delete")))
    {
        strrpc(buttonAllStr, "delete", "delete1 delete2 delete3 delete4 delete5 delete6 delete7 delete8");
    }
}

int isNumberBit(char* p)
{
    return *p >= '0' && *p <= '9';
}

int countBlankNum(char *strToCount, char charToFind) {
    int counter = 0;
    while (strchr(strToCount, charToFind)) {
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
        //隐含条件，先判定不是=》按钮，再判定是不是第一个数字才能确定是追加按钮
    else if (buttonStr[0] >= '0' && buttonStr[0] <= '9') {
        tempButton.type = APPEND;
        sscanf(buttonStr, "%d", &tempButton.attachedInfo.appendNum);
    } else if (strstr(buttonStr, "x^")) {
        tempButton.type = POW;
        sscanf(buttonStr, "x^%d", &tempButton.attachedInfo.exponent);
    } else if (strstr(buttonStr, "+/-")) {
        tempButton.type = SIGN_CONVERT;
    } else if (!strcmp(buttonStr, "reverse")) {
        tempButton.type = REVERSE;
    } else if (strstr(buttonStr, "shift")) {
        tempButton.type = SHIFT;
        //用操作数存储左移和或右移的信息
        if (strstr(buttonStr, ">")) {
            tempButton.attachedInfo.shiftDirection = SHIFT_RIGHT;
        } else if (strstr(buttonStr, "<")) {
            tempButton.attachedInfo.shiftDirection = SHIFT_LEFT;
        } else {
            tempButton.type = UNKNOW;
        }
    } else if (!strcmp(buttonStr, "mirror")) {
        tempButton.type = MIRROR;
    } else if (!strcmp(buttonStr, "sum")) {
        tempButton.type = SUM;
    } else if (!strcmp(buttonStr, "store")) {
        tempButton.type = STORE;
        tempButton.attachedInfo.storeNum = STORE_NOTHING;  //存储为-1表示没有存储相应的数字，短按将不能追加
    } else if (buttonStr[0] == '[' && buttonStr[2] == ']') {
        tempButton.type = MODIFY;
        tempButton.attachedInfo.modifyInfo.arithmeticSymbol = buttonStr[1];  //存储操作符
        sscanf(buttonStr + 3, "%d", &tempButton.attachedInfo.modifyInfo.operationNum);  //存储操作数
    } else if (!strcmp(buttonStr, "<<")) {
        tempButton.type = BACKSPACE;
    } else if (!strcmp(buttonStr, "lnv10")) {
        tempButton.type = LNV10;
    } else if (strstr(buttonStr, "sort")) {
        tempButton.type = SORT;
        //升序和降序的信息
        if (strstr(buttonStr, ">")) {
            tempButton.attachedInfo.sortType = SORT_ASCENDING;
        } else if (strstr(buttonStr, "<")) {
            tempButton.attachedInfo.sortType = SORT_DESCENDING;
        } else {
            tempButton.type = UNKNOW;
        }
    } else if(strstr(buttonStr, "cut")) {
        tempButton.type = CUT;
        sscanf(buttonStr, "cut%s", tempButton.attachedInfo.cutNum);
    } else if(strstr(buttonStr, "delete")) {
        tempButton.type = DELETE;
        sscanf(buttonStr, "delete%d", &tempButton.attachedInfo.deleteBit);
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
