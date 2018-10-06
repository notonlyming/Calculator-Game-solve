#ifndef _GAME_H_
#define _GAME_H_

#include "game_portal.h"

#define TRUE 1
#define FALSE 0
#define BUTTON_STR_MAX_LENGTH 10
#define NUMBER_STR_MAX_LENGTH 20
#define MAX_BUTTON_NUM 5
#define STORE_NOTHING -1
#define MAX_REPLACE_NUM_LENGTH 3

typedef enum
{
    APPEND,       //追加
    PLUS,         //算术加
    MINUS,        //算术减
    MULTIPLY,     //算术乘
    DIVIDE,       //算术除
    BACKSPACE,    //退格，既:<<
    REPLACE,      //替换
    POW,          //幂次方
    SIGN_CONVERT, //符号转换
    REVERSE,      //反转
    SUM,          //求每一位数字的和
    SHIFT,        //左右移动数字
	MIRROR,	      //镜像数字
    STORE,        //存储数字
    MODIFY,       //更改按钮的数值
    LNV10,        //每一位减去10 取绝对值 并取余10
    UNKNOW        //未知类型
} ButtonType;

typedef struct
{
    ButtonType type; //按钮类型
    union{
        int operationNum;  //用于存储加减乘除操作
        struct {
            char strReplaceFrom[MAX_REPLACE_NUM_LENGTH];
            char strReplaceTo[MAX_REPLACE_NUM_LENGTH];
        } replaceInfo;  //存储用于替换的值
        struct {
            char arithmeticSymbol;
            int operationNum;
        } modifyInfo;
        enum shiftDirection {SHIFT_RIGHT, SHIFT_LEFT} shiftDirection;  //移位方向
        int exponent;  //存储幂运算的指数
        int appendNum;  //追加到末尾的数字
        int storeNum;  //存储按钮存储区
    } attachedInfo;
} Button;            //存储按钮的详细信息

typedef struct storeOrNotAnswerList{
    union{
        short storeButtonCount;  //头节点存储了存储按钮的个数
        unsigned short *isStoreAnswer;  //单个store按钮对应存储方法
    };
    Button *storeButtonP;  //指向对应的store按钮，方便去按它
    struct storeOrNotAnswerList *next;
} storeOrNotAnswerList;

typedef storeOrNotAnswerList storeOrNotAnswerNode;

struct GameStruct
{
    int startNum;     //储存开始状态下游戏中屏幕显示的内容
    unsigned short buttonNum;    //按钮个数
    unsigned short allowMaxStep; //允许的最大步数
    int gameAchieve;  //游戏目标
    Button *buttons;  //按钮数组头指针
    unsigned short isOnError;  //判断计算是否出现错误，如出现小数
    unsigned short isButtonModify; //用于记录按钮是否被修改
    portal* portalPointer;  //传送门指针
    Button *unchangeButtons;  //如果按钮被更改，将会复制一份原始值到这里
    storeOrNotAnswerList *storeOrNotAnswerListHead;  //如果存在store按钮，将会在这里建立存储方案链表
};

char *buttonStr(Button button);
extern struct GameStruct Game;
void gameOver();
void resetButton();
void backupButton();
void freeStoreWayList();

#endif