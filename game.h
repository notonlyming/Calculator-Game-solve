#ifndef _GAME_H_
#define _GAME_H_

#define TRUE 1
#define FALSE 0
#define BUTTON_STR_MAX_LENGTH 10
#define NUMBER_STR_MAX_LENGTH 20
#define MAX_BUTTON_NUM 5
#define STORE_NOTHING -1

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
    UNKNOW        //未知类型
} ButtonTpye;

typedef struct
{
    ButtonTpye type; //按钮类型
    int number[2];     //操作数数组（最多存两个，也可只存一个）
} Button;            //存储按钮的详细信息

struct GameStruct
{
    int startNum;     //储存开始状态下游戏中屏幕显示的内容
    int buttonNum;    //按钮个数
    int allowMaxStep; //允许的最大步数
    int gameAchieve;  //游戏目标
    Button *buttons;  //按钮数组头指针
    unsigned short isOnError;  //判断计算是否出现错误，如出现小数
    unsigned short isButtonModify; //用于记录按钮是否被修改
    Button *unchangeButtons;  //如果按钮被更改，将会复制一份原始值到这里
    storeOrNotAnswerList *storeOrNotAnswerListHead;  //如果存在store按钮，将会在这里建立存储方案链表
};

typedef struct storeOrNotAnswerList{
    union{
        short storeButtonCount;  //头节点存储了存储按钮的个数
        short *isStoreAnswer;  //单个store按钮对应存储方法
    };
    Button *storeNuttonP;  //指向对应的store按钮，方便去按它
    struct storeOrNotAnswerList *next;
} storeOrNotAnswerList;

typedef storeOrNotAnswerList storeOrNotAnswerNode;

char *buttonStr(Button button);
extern struct GameStruct Game;
void gameOver();
void resetButton();
void backupButton();

#endif