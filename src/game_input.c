/*
 * 该文件用于实现程序的输入功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_input.h"
#include "game_output.h"

//该函数用于检测是否目标输入了字符，如果输入字符则转换为合适的数值。
void detectCharAndConvertToNumber(char* achieveStr)
{
    strlwr(achieveStr);
    int achieveStrLen = strlen(achieveStr);
    int code;  //字母所在字母表的编号，非ascii表
    int convertedCode = -1;  //转换后的数字
    for(int i = 0; i < achieveStrLen; i++)
    {
        if(achieveStr[i] >= 'a' && achieveStr[i] <= 'z')
        {
            code = achieveStr[i] - 96;
            // 除3向上取整
            if(code % 3 == 0)
            {
                convertedCode = code / 3;
            }
            else
            {
                convertedCode = code / 3 + 1;
            }
            printf("%c =======> %d\n", achieveStr[i], convertedCode);
            achieveStr[i] = '0' + convertedCode;
        }
    }
    if(convertedCode != -1)
    {
        printf("新的游戏目标：%s\n", achieveStr);
    }
}

// 该函数用于获取游戏目标，因为游戏目标有多个，因此单独一个函数处理
// 返回从用户输入处获得的目标数组(int)，记得free.
// 参数为返回目标数组的元素总数。
int* getGameAchieve(int* achieveCount, short isSilent)
{
    char achieveStr[NUMBER_STR_MAX_LENGTH];
    if(!isSilent) printf("请输入游戏目标：");
    fgets(achieveStr, NUMBER_STR_MAX_LENGTH, stdin);
    achieveStr[strlen(achieveStr) - 1] = '\0';   //除去末尾的换行符
    detectCharAndConvertToNumber(achieveStr);
    
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
struct GameStruct *getGameLevelInfo(short isSilent) {
    if(!isSilent) printf("请输入计算器起始的数值：");
    scanf("%d", &(Game.startNum));

    if(!isSilent) printf("请输入允许的最大步数：");
    scanf("%hu", &(Game.allowMaxStep));
    getchar();  //拿掉换行符

    //读入按钮信息字符串
    char buttonAllStr[BUTTON_STR_MAX_LENGTH * MAX_BUTTON_NUM];
    if(!isSilent) printf("请输入按钮信息(单个空格分隔,回车结束)：");
    fgets(buttonAllStr, BUTTON_STR_MAX_LENGTH * MAX_BUTTON_NUM, stdin);
    buttonAllStr[strlen(buttonAllStr) - 1] = '\0';  //除去末尾的换行符
    strlwr(buttonAllStr);   // 全部转换为小写，方便处理
    detectAndInsertDeleteButton(buttonAllStr);
    detectAndInsertShiftButton(buttonAllStr);
    detectAndInsertReplaceButton(buttonAllStr);
    detectAndInsertRoundButton(buttonAllStr);
    detectAndInsertInsertButton(buttonAllStr);
    detectAndInsertBitPlusButton(buttonAllStr);

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
    getAndInitialisePortal(isSilent);
    if(!isSilent) printButtons(Game.buttons, Game.buttonNum);
    return &Game;
}

// 传入用户输入的按钮字符串，如果内含独立的delete则替换为8个独立的delete以实现删除任意位。
void detectAndInsertDeleteButton(char* buttonAllStr)
{
    //基于delete只有一个这一事实，使用替换。
    char* deleteStrStartP = strstr(buttonAllStr, "delete");
    // 如果包含delete字符串，且后边不跟数字，则需要替换！
    if(deleteStrStartP && !isNumberBit(deleteStrStartP + strlen("delete")))
    {
        strrpc(buttonAllStr, "delete", "delete1 delete2 delete3 delete4 delete5 delete6");
    }
}

void detectAndInsertShiftButton(char* buttonAllStr)
{
    //基于shift只有一个这一事实，使用替换。
    char* shiftStrStartP = strstr(buttonAllStr, "shift");
    // 如果包含shift字符串，且后边不跟数字，则需要替换！
    if(shiftStrStartP && !isNumberBit(shiftStrStartP + strlen("shift")))
    {
        strrpc(buttonAllStr, "shift", "shift1 shift2 shift3 shift4 shift5 shift6");
    }
}

// 传入用户输入的按钮字符串，如果内含独立的round则替换为6个独立的round以实现删除任意位。
void detectAndInsertRoundButton(char* buttonAllStr)
{
    //基于round按钮只可能有一个这个事实，使用替换。
    char* roundStrStartP = strstr(buttonAllStr, "round");
    // 如果包含round字符串，且后边不跟数字，则需要替换！
    if(roundStrStartP && !isNumberBit(roundStrStartP + strlen("round")))
    {
        strrpc(buttonAllStr, "round", "round1 round2 round3 round4 round5 round6");
    }
}

// 传入用户输入的按钮字符串，如果内含replace则替换为任意位以实现替换任意位。
void detectAndInsertReplaceButton(char* buttonAllStr)
{
    char* replaceStrStartP;
    int numberToReplace;
    char replaceStr[BUTTON_STR_MAX_LENGTH];
    // 如果包含replace字符串，且前边没指定数字，且后边有数字，则需要替换！
    while( 
        ((replaceStrStartP = strstr(buttonAllStr, "replace")) &&
        !isNumberBit(replaceStrStartP - 1) && isNumberBit(replaceStrStartP + strlen("replace"))) ||
        (replaceStrStartP = strstr(buttonAllStr, " replace"))
    )
    {
        if (replaceStrStartP[0] != ' ') sscanf(replaceStrStartP, "replace%d", &numberToReplace);
        else sscanf(replaceStrStartP, " replace%d", &numberToReplace);
        sprintf(replaceStr, "1replace%d 2replace%d 3replace%d 4replace%d 5replace%d 6replace%d 7replace%d 8replace%d",
        numberToReplace, numberToReplace, numberToReplace, numberToReplace,
        numberToReplace, numberToReplace, numberToReplace, numberToReplace
        );
        char before[BUTTON_STR_MAX_LENGTH];
        memset(before, 0, sizeof(before));
        // 复制replace前面的部分，注意这里复制不包括replace前面的数字
        strncpy(before, buttonAllStr, replaceStrStartP - buttonAllStr);
        strcat(before, replaceStr);
        strcat(before, replaceStrStartP + strlen("replace?"));
        strcpy(buttonAllStr, before);
    }
}

// 传入用户输入的按钮字符串，如果内含insert则替换为任意位以实现插入任意位。
void detectAndInsertInsertButton(char* buttonAllStr)
{
    char* insertStrStartP;
    int numberToInsert;
    char insertStr[BUTTON_STR_MAX_LENGTH];
    // 如果包含insert字符串，且前边没指定数字，且后边有数字，则需要替换！
    while( 
        ((insertStrStartP = strstr(buttonAllStr, "insert")) &&
        !isNumberBit(insertStrStartP - 1) && isNumberBit(insertStrStartP + strlen("insert"))) ||
        (insertStrStartP = strstr(buttonAllStr, " insert"))
    )
    {
        if (insertStrStartP[0] != ' ') sscanf(insertStrStartP, "insert%d", &numberToInsert);
        else sscanf(insertStrStartP, " insert%d", &numberToInsert);
        sprintf(insertStr, "1insert%d 2insert%d 3insert%d 4insert%d 5insert%d 6insert%d",
        numberToInsert, numberToInsert, numberToInsert,
        numberToInsert, numberToInsert, numberToInsert
        );
        char before[BUTTON_STR_MAX_LENGTH];
        // 复制replace前面的部分
        memset(before, 0, sizeof(before));
        strncpy(before, buttonAllStr, insertStrStartP - buttonAllStr);
        strcat(before, insertStr);
        strcat(before, insertStrStartP + strlen("insert?"));
        strcpy(buttonAllStr, before);
    }
}

// 传入用户输入的按钮字符串，如果内含bitPlus则替换为任意位以实现插入任意位。
void detectAndInsertBitPlusButton(char* buttonAllStr)
{
    char* bitPlusStrStartP;
    int numberToPlus;
    char bitPlusStr[BUTTON_STR_MAX_LENGTH];
    // 如果包含bitPlus字符串，且前边没指定数字，且后边有数字，则需要替换！
    while( 
        ((bitPlusStrStartP = strstr(buttonAllStr, "bit+")) &&
        !isNumberBit(bitPlusStrStartP - 1) && isNumberBit(bitPlusStrStartP + strlen("bit+"))) ||
        (bitPlusStrStartP = strstr(buttonAllStr, " bit+"))
    )
    {
        if (bitPlusStrStartP[0] != ' ') sscanf(bitPlusStrStartP, "bit+%d", &numberToPlus);
        else sscanf(bitPlusStrStartP, " bit+%d", &numberToPlus);
        sprintf(bitPlusStr, "1bit+%d 2bit+%d 3bit+%d 4bit+%d 5bit+%d 6bit+%d",
        numberToPlus, numberToPlus, numberToPlus,
        numberToPlus, numberToPlus, numberToPlus
        );
        char before[BUTTON_STR_MAX_LENGTH];
        // 复制bit+前面的部分
        memset(before, 0, sizeof(before));
        strncpy(before, buttonAllStr, bitPlusStrStartP - buttonAllStr);
        strcat(before, bitPlusStr);
        strcat(before, bitPlusStrStartP + strlen("bit+?"));
        strcpy(buttonAllStr, before);
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
    } else if(strstr(buttonStr, "replace")) {
        char* replaceStrStartP = strstr(buttonStr, "replace");
        // 如果指定了位，则符合指定位替换按钮。
        // 未指定位则为任意位替换，应当在传入之前就被船利为8个替换位按钮。
        if(isNumberBit(replaceStrStartP - 1))
        {
            tempButton.type = REPLACE_BIT;
            sscanf(buttonStr, "%hdreplace%c", &tempButton.attachedInfo.rplBitInfo.replaceBit,
            &tempButton.attachedInfo.rplBitInfo.replaceNumberChar);
        }
    } else if(strstr(buttonStr, "insert")) {
        char* insertStrStartP = strstr(buttonStr, "insert");
        // 类似上面的替换按钮
        if(isNumberBit(insertStrStartP - 1))
        {
            tempButton.type = INSERT;
            sscanf(buttonStr, "%hdinsert%c", &tempButton.attachedInfo.insertBitInfo.insertBit,
            &tempButton.attachedInfo.insertBitInfo.insertNumberChar);
        }
    } else if(strstr(buttonStr, "bit+")) {
        char* plusStrStartP = strstr(buttonStr, "bit+");
        // 类似上面的按钮
        if(isNumberBit(plusStrStartP - 1))
        {
            tempButton.type = BIT_PLUS;
            sscanf(buttonStr, "%hdbit+%c", &tempButton.attachedInfo.plusBitInfo.plusBit,
            &tempButton.attachedInfo.plusBitInfo.plusNumberChar);
        }
    }
        //隐含条件，先排除第一个是用于表示位的数字的特殊功能按钮，再判定第一个是数字才能确定是追加按钮
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
        } else if (buttonStr[strlen(buttonStr) - 1] > '0' && buttonStr[strlen(buttonStr) - 1] < '9')  {
            tempButton.type = SHIFT_TIMES;
            tempButton.attachedInfo.shiftTimes = buttonStr[strlen(buttonStr) - 1] - 48;
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
        sscanf(buttonStr, "delete%zd", &tempButton.attachedInfo.deleteBit);
    } else if(strstr(buttonStr, "round")) {
        tempButton.type = ROUND;
        sscanf(buttonStr, "round%zd", &tempButton.attachedInfo.roundBit);
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
