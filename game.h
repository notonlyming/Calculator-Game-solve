#define TRUE 1
#define FALSE 0
#define BUTTON_STR_MAX_LENGTH 10
#define NUMBER_STR_MAX_LENGTH 20

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
    UNKNOW        //未知类型
} ButtonTpye;

typedef struct
{
    ButtonTpye type; //按钮类型
    int *number;     //操作数指针，如果是数组（多个操作数），就是头指针
} Button;            //存储按钮的详细信息

struct GameStruct
{
    int startNum;     //储存开始状态下游戏中屏幕显示的内容
    int buttonNum;    //按钮个数
    int allowMaxStep; //允许的最大步数
    int gameAchieve;  //游戏目标
    Button *buttons;  //按钮数组头指针
    short isOnError;  //判断计算是否出现错误，如出现小数
};

char *buttonStr(Button button);
extern struct GameStruct Game;