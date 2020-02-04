#ifndef _GAME_H_
#define _GAME_H_

#include "game_portal.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define BUTTON_STR_MAX_LENGTH 500
#define NUMBER_STR_MAX_LENGTH 30
#define MAX_BUTTON_NUM 15
#define MAX_ACHIEVE_NUM 5
#define STORE_NOTHING (-1)
#define MAX_REPLACE_NUM_LENGTH 3
#define CUT_MAX_LENGTH 5
#define MAX_BIT 8

typedef enum {
    APPEND,       //追加
    PLUS,         //算术加
    MINUS,        //算术减
    MULTIPLY,     //算术乘
    DIVIDE,       //算术除
    BIT_PLUS,     //按位加
    BACKSPACE,    //退格，既:<<
    REPLACE,      //替换
    REPLACE_BIT,  //按位替换
    POW,          //幂次方
    SIGN_CONVERT, //符号转换
    REVERSE,      //反转
    SUM,          //求每一位数字的和
    SHIFT,        //左右移动数字
    SHIFT_TIMES,  //多次移动数字
    MIRROR,       //镜像数字
    STORE,        //存储数字
    MODIFY,       //更改按钮的数值
    SORT,         //对暂存区中的数字排序
    LNV10,        //每一位减去10 取绝对值 并取余10
    CUT,          //删除特定数字
    ROUND,        //对任意位四舍五入，位右边全部置零
    DELETE,       //删除任意位上的数字
    INSERT,       //在某一位 “前” 插入。因此传入的位索引是1~长度加1
    UNKNOW        //未知类型
} ButtonType;

typedef struct {
    ButtonType type; //按钮类型
    union {
        int operationNum;  //用于存储加减乘除操作
        struct {
            char strReplaceFrom[MAX_REPLACE_NUM_LENGTH];
            char strReplaceTo[MAX_REPLACE_NUM_LENGTH];
        } replaceInfo;  //存储用于替换的值
        struct {
            char arithmeticSymbol;
            int operationNum;
        } modifyInfo;
        enum direction {
            SHIFT_RIGHT, SHIFT_LEFT
        } shiftDirection;  //移位方向
        enum sort {
            SORT_DESCENDING, SORT_ASCENDING
        } sortType;  //排序类型
        int exponent;  //存储幂运算的指数
        int appendNum;  //追加到末尾的数字
        int storeNum;  //存储按钮存储区
        char cutNum[CUT_MAX_LENGTH];   //要删除的东西
        size_t deleteBit;   //删除操作所在位置，左边数起，从1开始
        size_t roundBit;  //要四舍五入的位，左边数起，从1开始
        struct replaceBitInfo {
            unsigned short replaceBit;
            char replaceNumberChar;
        } rplBitInfo;   //按位替换的附加信息
        struct insertBitInfo {
            unsigned short insertBit;
            char insertNumberChar;
        } insertBitInfo;   //按位替换的附加信息
        struct plusBitInfo {
            unsigned short plusBit;
            char plusNumberChar;
        } plusBitInfo;
        int shiftTimes;    //移位次数
    } attachedInfo;
} Button;            //存储按钮的详细信息

typedef struct {
    unsigned short *isStoreAnswer;  //单个store按钮对应存储方法
    Button *storeButtonP;  //指向对应的store按钮，方便去按它
} storeOrNotAnswerStruct;

struct GameStruct {
    int startNum;     //储存开始状态下游戏中屏幕显示的内容
    unsigned short buttonNum;    //按钮个数
    unsigned short allowMaxStep; //允许的最大步数
    int gameAchieve;  //游戏目标
    Button *buttons;  //按钮数组头指针
    unsigned short isOnError;  //判断计算是否出现错误，如出现小数
    unsigned short isButtonModify; //用于记录按钮是否被修改
    portal *portalPointer;  //传送门指针
    Button *unchangedButtons;  //如果按钮被更改，将会复制一份原始值到这里
    storeOrNotAnswerStruct *storeOrNotAnswerStructP;  //如果存在store按钮，将会在这里建立存储方案链表
    short hasABC;  // 如果为真，则最终输出解包含ABC按钮
};

extern struct GameStruct Game;

char *buttonStr(Button button);

void gameOver();

void resetButton();

void backupButton();

void freeStoreWayList();

#endif