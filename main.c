/*
 * 这是一个用来计算一个叫Calculator游戏的小程序
 * Calculator是一个萌萌的计算器游戏
 * 通过限定次数，和用指定的按键来得到最终的结果
 * 这是一个数学游戏
 * 程序通过穷尽所有的组合来得到结果
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BUTTON_STR_MAX_LENGTH 10
#define NUMBER_STR_MAX_LENGTH 20
#define TRUE 1
#define FALSE 0

typedef enum
{
    APPEND,//追加
    PLUS,//算术加
    MINUS,//算术减
    MULTIPLY,//算术乘
    DIVIDE,//算术除
    BACKSPACE,//退格，既:<<
    REPLACE,//替换
    SQUARE,//平方
    SIGN_CONVERT,//符号转换
    UNKNOW//未知类型
} ButtonTpye;

typedef struct
{
    ButtonTpye type; //按钮类型
    int *number;     //操作数指针，如果是数组（多个操作数），就是头指针
} Button;            //存储按钮的详细信息

struct
{
    int startNum;     //储存开始状态下游戏中屏幕显示的内容
    int buttonNum;    //按钮个数
    int allowMaxStep; //允许的最大步数
    int gameAchieve;  //游戏目标
    Button *buttons;  //按钮数组头指针
    short isOnError;  //判断计算是否出现错误，如出现小数
} Game = {.isOnError = FALSE};

void printButtons(Button buttons[], int buttonNumber);
int calculateNumberLength(int number);
int pressButton(Button buttonToPress, int currentNumber);
void getGameLevelInfo();
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix);
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth);
void solveIt();
Button analyseButtonStr(char *buttonStr);
char *buttonStr(Button button);
int numberReplace(int number, int fromNum, int toNum);

int main(void)
{
    do
    {
        getGameLevelInfo();
        solveIt();
        puts("温馨提示：退出请按Ctrl+C");
        puts("-----------------新的一关开始啦-----------------");
    } while (1);
    return 0;
}

//该函数用于取得按钮对应信息的字符串
char *buttonStr(Button button)
{
    char *infoStr = (char *)malloc(sizeof(char) * BUTTON_STR_MAX_LENGTH);
    switch (button.type)
    {
    case PLUS:
        sprintf(infoStr, "＋%i", *(button.number));
        break;
    case MINUS:
        sprintf(infoStr, "－%i", *(button.number));
        break;
    case MULTIPLY:
        sprintf(infoStr, "×%i", *(button.number));
        break;
    case DIVIDE:
        sprintf(infoStr, "÷%i", *(button.number));
        break;
    case BACKSPACE:
        infoStr = "<<";
        break;
    case APPEND:
        sprintf(infoStr, "%i", *(button.number));
        break;
    case REPLACE:
        sprintf(infoStr, "%i=>%i", button.number[0], button.number[1]);
        break;
    case SQUARE:
        infoStr = "x^2";
        break;
    case SIGN_CONVERT:
        infoStr = "+/-";
        break;
    case UNKNOW:
        infoStr = "unkown";
        break;
    }
    return infoStr;
}

void printButtons(Button buttons[], int buttonNumber)
{
    printf("-----------------当前已有按钮-----------------\n");
    for (int i = 0; i < buttonNumber; i++)
    {
        printf("按钮%i：【%s】\n", i, buttonStr(buttons[i]));
    }
    printf("---------------------------------------------\n");
}

int calculateNumberLength(int number)
{
    if (number == 0)
    {
        return 1;
    }
    else
    {
        int count = 0;
        while (number > 0)
        {
            number /= 10;
            count++;
        }
        return count;
    }
}

//该函数将一个数字中的某部分替换乘另外一部分，并返回替换后的数字
int numberReplace(int number, int fromNum, int toNum)
{
    char numberStr[NUMBER_STR_MAX_LENGTH] = {0},
         fromNumStr[NUMBER_STR_MAX_LENGTH] = {0},
         toNumStr[NUMBER_STR_MAX_LENGTH] = {0};
    sprintf(numberStr, "%i", number);
    sprintf(fromNumStr, "%i", fromNum);
    sprintf(toNumStr, "%i", toNum);
    char *startPosition, *endPosition;
    char *strP = numberStr; //用于查找替换的指针，初始化为数字字符串的头部表示从头开始找
    //要么已经查找到了末尾，要么找不到要替换的子串了
    while (strP != (numberStr + strlen(numberStr)) && strstr(strP, fromNumStr) != NULL)
    {
        //查找要替换的字符串
        startPosition = strstr(strP, fromNumStr);
        endPosition = startPosition + strlen(fromNumStr);
        //截断
        numberStr[startPosition - numberStr] = '\0';
        //拼接
        sprintf(numberStr, "%s%s%s", numberStr, toNumStr, numberStr + (endPosition - numberStr));
        //前面的已经查找并替换过了，现在查找指针移到后面
        strP = endPosition;
    }
    sscanf(numberStr, "%i", &number); //转换为整型
    return number;
}

int pressButton(Button buttonToPress, int currentNumber)
{
    int result = currentNumber;
    switch (buttonToPress.type)
    {
    case PLUS:
        result += *(buttonToPress.number);
        break;
    case MINUS:
        result -= *(buttonToPress.number);
        break;
    case MULTIPLY:
        result *= *(buttonToPress.number);
        break;
    case DIVIDE:
        //进行是否产生小数判断
        if ( result % *(buttonToPress.number) != 0 )
        {
            Game.isOnError = TRUE;
        }
        else
        {
            result /= *(buttonToPress.number);
        }
        break;
    case BACKSPACE:
        result = (int)(result / 10);
        break;
    case APPEND:
        if (result >= 0)
            result = result * pow(10, calculateNumberLength(*(buttonToPress.number))) + *(buttonToPress.number);
        else
            result = result * pow(10, calculateNumberLength(*(buttonToPress.number))) - *(buttonToPress.number);
        break;
    case REPLACE:
        result = numberReplace(result, buttonToPress.number[0], buttonToPress.number[1]);
        break;
    case SQUARE:
        result = result * result;
        break;
    case SIGN_CONVERT:
        result *= -1;
        break;
    case UNKNOW:; //do nothing
        break;
    }
    return result;
}

//将传入的按钮字符串解析为按钮结构
Button analyseButtonStr(char *buttonStr)
{
    Button tempButton = {.type = UNKNOW, .number = NULL};
    //解析按钮是不是加减乘除
    switch (buttonStr[0])
    {
    case '+':
        tempButton.type = PLUS;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "+%i\n", tempButton.number);
        break;
    case '-':
        tempButton.type = MINUS;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "-%i", tempButton.number);
        break;
    case '*':
        tempButton.type = MULTIPLY;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "*%i", tempButton.number);
        break;
    case '/':
        tempButton.type = DIVIDE;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "/%i", tempButton.number);
        break;
    case '<':
        tempButton.type = BACKSPACE;
        tempButton.number = NULL;
        break;
    }
    if (strstr(buttonStr, "=>"))
    {
        tempButton.type = REPLACE;
        tempButton.number = (int *)malloc(sizeof(int) * 2);
        sscanf(buttonStr, "%i=>%i", tempButton.number, tempButton.number + 1);
    }
    else if (buttonStr[0] >= '0' && buttonStr[0] <= '9')
    {
        tempButton.type = APPEND;
        tempButton.number = (int *)malloc(sizeof(int));
        sscanf(buttonStr, "%i", tempButton.number);
    }
    else if (strstr(buttonStr, "x^2"))
    {
        tempButton.type = SQUARE;
        tempButton.number = NULL;
    }
    else if (strstr(buttonStr, "+/-"))
    {
        tempButton.type = SIGN_CONVERT;
        tempButton.number = NULL;
    }
    if (tempButton.type == UNKNOW)
    {
        fprintf(stderr, "啊啊啊，您输入了无法识别的按钮信息~\n程序将退出！\n");
        exit(1);
    }
    return tempButton;
}

void getGameLevelInfo()
{
    printf("请输入计算器起始的数值：");
    scanf("%i", &(Game.startNum));

    printf("请输入允许的最大步数：");
    scanf("%i", &(Game.allowMaxStep));

    printf("请输入游戏目标：");
    scanf("%i", &(Game.gameAchieve));

    printf("请输入有多少个按钮：");
    scanf("%i", &(Game.buttonNum));
    getchar(); //拿掉换行符
    Game.buttons = (Button *)malloc(sizeof(Button) * Game.buttonNum);

    char buttonStr[BUTTON_STR_MAX_LENGTH];
    for (int i = 0; i < Game.buttonNum; i++)
    {
        printf("请输入按钮信息(操作符和数字)：");
        fgets(buttonStr, sizeof(buttonStr), stdin);
        Game.buttons[i] = analyseButtonStr(buttonStr);
        printButtons(Game.buttons, i + 1);
    }
}

//有必要写一个为某一进制位加一的函数减轻复杂度,直接加1返回0，发生进位返回-1
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix)
{
    if (number[witchBit] + 1 != radix)
    {
        number[witchBit] += 1;
        return 0;
    }
    else
    {
        //发生进位
        number[witchBit] = 0;
        return -1;
    }
}

//该函数用于实现特定的进制数加1，多少进制的数用来表示那个按钮按下，当进制数溢出，返回-1，即为所有情况试错完成，否则返回0
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth)
{
    unsigned short witchBit;
    for (witchBit = 0; witchBit < numberWidth; witchBit++)
    {
        if (bitAdd(number, witchBit, radix) == 0)
        {
            //位加1成功且未发生进位
            break;
        }
        else
        {
            //位加1成功，发生进位
            if (witchBit == numberWidth - 1)
            {
                //已经"溢出"，恢复状态
                number[witchBit] = radix - 1;
                return -1;
            }
            else
            {
                //未溢出，继续给高位加一
                continue;
            }
        }
    }
    //加一操作顺利结束，未发生数满溢出
    return 0;
}

void solveIt()
{
    int tempResult;                                                                                //试错临时结果变量
    unsigned short *answer = (unsigned short *)malloc(sizeof(unsigned short) * Game.allowMaxStep); //用于存储解的过程

    //从最少的步数开始尝试，看看有没有最优解
    for (int stepsNum = 1; stepsNum <= Game.allowMaxStep; stepsNum++)
    {
        for (int i = 0; i < Game.allowMaxStep; i++)
            answer[i] = 0; //所有位初始化为0
        do
        {
            tempResult = Game.startNum;
            //逐个"按下"按钮
            for (int step = 0; step < stepsNum; step++)
            {
                tempResult = pressButton(Game.buttons[answer[step]], tempResult);
                if (Game.isOnError == TRUE)
                {
                    //已经计算出错，此方案不可行
                    break;
                }
            }
            //判断是否成功
            if (tempResult == Game.gameAchieve && Game.isOnError == FALSE)
            {
                printf("发现解(%d步)：", stepsNum);
                //打印解
                for (int step = 0; step < stepsNum; step++)
                {
                    printf("(%s) ", buttonStr(Game.buttons[answer[step]]));
                }
                printf("结果：%d", tempResult);
                putchar('\n');
            }
            else //本次尝试失败
            {
                //重置错误状态
                Game.isOnError = FALSE;
            }
        } while (numerationAddOne(answer, Game.buttonNum, stepsNum) != -1);
    }
}
