/*
 * 计算数字长度
 * 按下按钮
 * 位加一
 * 特定进制数加一
 * 数字子串替换
 * 反转数字
 * 数字按位求和
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "game.h"
#include <string.h>
#include "game_output.h"
#include "game_process.h"
#include "stepObserver.h"

int reverseNum(int number)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number); //转成字符串
    strReverse(numberStr);
    sscanf(numberStr, "%d", &number); //转回数值
    //反转负值时带上负号
    if (numberStr[strlen(numberStr) - 1] == '-')
    {
        number *= -1;
    }
    return number;
}

//反转字符串
void strReverse(char stringToReverse[])
{
    //开始反转
    char tempChar;
    for (unsigned short index = 0; index < (strlen(stringToReverse) / 2); index++)
    {
        tempChar = stringToReverse[index];
        stringToReverse[index] = stringToReverse[strlen(stringToReverse) - 1 - index];
        stringToReverse[strlen(stringToReverse) - 1 - index] = tempChar;
    }
}

int calculateNumberLength(int number)
{
    if (number == 0)
    {
        return 1;
    }
    else
    {
        if(number < 0)
        {
            number *= -1;
        }
        int count = 0;
        while (number > 0)
        {
            number /= 10;
            count++;
        }
        return count;
    }
}

//该函数将一个数字中的某部分替换成另外一部分，并返回替换后的数字
int numberReplace(int number, char *fromNumStr, char *toNumStr)
{
    char numberStr[NUMBER_STR_MAX_LENGTH] = {0};
    char newNumStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    char *startPosition, *endPosition;
    char *strP = numberStr; //用于查找替换的指针，初始化为数字字符串的头部表示从头开始找
    if (strstr(strP, fromNumStr) == NULL)
    {
        //如果没有可替换的字串，说明这次替换按钮是无效的
        Game.isOnError = TRUE;
    }
    else
    {
        //要么已经查找到了末尾，要么找不到要替换的子串了
        while (strP != (numberStr + strlen(numberStr)) && strstr(strP, fromNumStr) != NULL)
        {
            //查找要替换的字符串
            startPosition = strstr(strP, fromNumStr);
            endPosition = startPosition + strlen(fromNumStr);
            //截断
            *startPosition = '\0';
            //拼接
            sprintf(newNumStr, "%s%s%s", numberStr, toNumStr, endPosition);
            strcpy(numberStr, newNumStr);
            //前面的已经查找并替换过了，现在查找指针移到后面
            strP = endPosition + (strlen(toNumStr) - strlen(fromNumStr));
        }
    }
    sscanf(newNumStr, "%d", &number); //转换为整型
    return number;
}

//左移或右移数字，返回移动后的数字
int shiftNumber(int number, enum shiftDirection direction)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    char newNumStr[NUMBER_STR_MAX_LENGTH];
    short sign = (short) (number >= 0 ? +1 : -1);  //记录符号
    if (sign == 1)
    {
        sprintf(numberStr, "%d", number);  //取出
    }
    else
    {
        sprintf(numberStr, "%d", -number);  //取出
    }
    if (direction == SHIFT_RIGHT)
    {
        char tempChar;  //用于存储因向右移位被“挤”出来的字符
        tempChar = numberStr[strlen(numberStr)-1];
        numberStr[strlen(numberStr)-1] = '\0';
        sprintf(newNumStr, "%c%s", tempChar, numberStr);
    }
    else if(direction == SHIFT_LEFT)
    {
        sprintf(newNumStr, "%s%c", numberStr + 1, numberStr[0]);
    }
    else
    {
        Game.isOnError = TRUE;
    }
    sscanf(newNumStr, "%d", &number); //转换为整型
    return number*sign;
}

//mirror number, retern ok number
int mirrorNumber(int number)
{
	char numberStr[NUMBER_STR_MAX_LENGTH];
	char reverseNumberStr[NUMBER_STR_MAX_LENGTH];
	short sign = (short) (number >= 0 ? +1 : -1);
	if (number < 0)
	{
		number *= -1;
	}
	sprintf(numberStr, "%d", number);
	sprintf(reverseNumberStr, "%d", number);
    strReverse(reverseNumberStr);
	strcat(numberStr, reverseNumberStr);
    sscanf(numberStr, "%d", &number); //转换为整型
	return number * sign ;
}

//求每一位数字的和并返回求和后的数字,这里假设求和的数字必须是正的
int numberSum(int number)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);  //取出
    unsigned short tempNum;
    number = 0;  //结果先初始化为0
    if (numberStr[0] != '-')
    {
        for (unsigned int i=0; i<strlen(numberStr); i++)
        {
            tempNum = (unsigned short) (numberStr[i] - '0');  //取出一位
            number += tempNum;
        }
    }
    else
    {
        for (unsigned int i=1; i<strlen(numberStr); i++)
        {
            tempNum = (unsigned short) (numberStr[i] - '0');  //取出一位
            number += tempNum;
        }
        number *= -1;
    }
    return number;
}

int pressButton(Button buttonToPress, int currentNumber)
{
    int result = currentNumber;
    switch (buttonToPress.type)
    {
    case PLUS:
        result += buttonToPress.attachedInfo.operationNum;
        break;
    case MINUS:
        result -= buttonToPress.attachedInfo.operationNum;
        break;
    case MULTIPLY:
        result *= buttonToPress.attachedInfo.operationNum;
        break;
    case DIVIDE:
        //进行是否产生小数判断
        if (result % buttonToPress.attachedInfo.operationNum != 0)
        {
            Game.isOnError = TRUE;
        }
        else
        {
            result /= buttonToPress.attachedInfo.operationNum;
        }
        break;
    case BACKSPACE:
        result = result / 10;
        break;
    case APPEND:
        result = numberAppend(result, buttonToPress.attachedInfo.appendNum);
        break;
    case REPLACE:
        result = numberReplace(result, buttonToPress.attachedInfo.replaceInfo.strReplaceFrom, buttonToPress.attachedInfo.replaceInfo.strReplaceTo);
        break;
    case POW:
        result = (int) pow( result, buttonToPress.attachedInfo.exponent );
        break;
    case SIGN_CONVERT:
        result *= -1;
        break;
    case REVERSE:
        result = reverseNum(result);
        break;
    case SUM:
        result = numberSum(result);
        break;
    case SHIFT:
        result = shiftNumber(result, buttonToPress.attachedInfo.shiftDirection);
		break;
	case MIRROR:
		result = mirrorNumber(result);
		break;
    case MODIFY:
        modifyButtons(buttonToPress.attachedInfo.modifyInfo.arithmeticSymbol,
                      buttonToPress.attachedInfo.modifyInfo.operationNum);
        break;
    case STORE:
        //这里仅处理短按
        if (buttonToPress.attachedInfo.storeNum >= 0)
            result = numberAppend(result, buttonToPress.attachedInfo.storeNum);
        else
            Game.isOnError = TRUE;
        break;
    case LNV10:
        result = lnv10(result);
        break;
    case UNKNOW:; //do nothing
    break;
    }
	checkNumberLarge(result);
    return result;
}

int lnv10(int number)
{
    short sign;
    if (number >= 0) {
        sign = (short) +1;
    } else {
        sign = (short) -1;
        number *= -1;
    }
    unsigned short numberLength = (unsigned short) calculateNumberLength(number);
    unsigned short *numberBit = (unsigned short*)malloc(numberLength * sizeof(unsigned short));
    //取出每一位
    for (int i=0; i<numberLength; i++)
    {
        numberBit[i] = (unsigned short) (number % 10);
        number /= 10;
        numberBit[i] = (unsigned short) ((10 - numberBit[i]) % 10); //用10减去它
    }
    //放回每一位
    for (int i=0; i<numberLength; i++)
    {
        number += numberBit[i] * (int)pow(10, i);
    }
    return number*sign;
}

//这里处理长按
void storeNumberToButton(int currentNumber, Button *storeButton)
{
    if (Game.isButtonModify == FALSE)
    {
        backupButton();
    }
    if (currentNumber >= 0)
    {
        storeButton->attachedInfo.storeNum = currentNumber;
    }
    else
    {
        Game.isOnError = TRUE;
    }
}

int numberAppend(int sourceNum, int numberToAppend)
{
    if (sourceNum >= 0)
        sourceNum = (int) (sourceNum * pow(10, calculateNumberLength(numberToAppend)) + numberToAppend);
    else
        sourceNum = (int) (sourceNum * pow(10, calculateNumberLength(numberToAppend)) - numberToAppend);
    return sourceNum;
}

//检查结果的数字是否超过6位，如果超过，game.error为真，该方案无效
int checkNumberLarge(int number)
{
	if (number > 999999 || number < -99999)
	{
		Game.isOnError = TRUE;
	}
	return number;
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
                number[witchBit] = (unsigned short) (radix - 1);
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

void creatStoreAnswerListForStoreButton()
{
    //计算存储按钮的个数
    short storeButtonIndex[MAX_BUTTON_NUM];  //记录按钮的索引信息，方便后面添加该按钮到存储方案链表里
    short storeButtonCounter = 0;
    for (short i=0; i<Game.buttonNum; i++)
    {
        if (Game.buttons[i].type == STORE)
        {
            storeButtonIndex[storeButtonCounter] = i;  //记录索引信息
            storeButtonCounter++;  //计数器加一
        }
    }
    if (storeButtonCounter != 0)
    {
        //创建头节点
        Game.storeOrNotAnswerListHead = (storeOrNotAnswerNode*)malloc(sizeof(storeOrNotAnswerNode));
        Game.storeOrNotAnswerListHead->storeButtonCount = storeButtonCounter;
        //创建存储方案链表
        storeOrNotAnswerNode *tailP = Game.storeOrNotAnswerListHead;
        for (int i=0; i<Game.storeOrNotAnswerListHead->storeButtonCount; i++)
        {
            //创建新节点
            tailP->next = (storeOrNotAnswerNode*)malloc(sizeof(storeOrNotAnswerNode));
            //指针后移
            tailP = tailP->next;
            //结尾next先赋值NULL
            tailP->next = NULL;
            //为新添加的节点指明它对应的是哪个按钮的存储方案
            tailP->storeButtonP = &(Game.buttons[storeButtonIndex[i]]);
            //创建插空法存储方案数组
            tailP->isStoreAnswer = malloc( sizeof(tailP->isStoreAnswer[0]) * Game.allowMaxStep );
            //数组元素初始化为0表示不按
            for (int j=0; j<Game.allowMaxStep; j++)
            {
                tailP->isStoreAnswer[j] = 0;
            }
        }
    }
}

void initAllIsStoreAnswer()
{
    storeOrNotAnswerNode *listP = Game.storeOrNotAnswerListHead;
    if (listP)
    {
        listP = listP->next;
        while (listP)
        {
            for (int i = 0; i < Game.allowMaxStep; i++)
                listP->isStoreAnswer[i] = 0; //所有位初始化为0
            listP = listP->next;
        }
    }
}

//尝试所有可能，并返回由尝试次数和解的个数构成的数组地址，需要传入用于存储计数的数组
unsigned int* solveIt(unsigned int counter[2], short isOutputSteps)
{
    int tempResult;    //试错临时结果变量
    unsigned short *answer = (unsigned short *)malloc(sizeof(unsigned short) * Game.allowMaxStep); //用于存储解的过程
    counter[0] = 0;  //尝试个数的计数器
    counter[1] = 0;  //求得解的个数计数器
    creatStoreAnswerListForStoreButton();

    //从最少的步数开始尝试，看看有没有最优解
    storeOrNotAnswerList *storeAnswer = NULL;  //存储当前尝试的store答案数组指针
    for (unsigned short stepsNum = 1; stepsNum <= Game.allowMaxStep; stepsNum++)
    {
        for (int i = 0; i < Game.allowMaxStep; i++)
            answer[i] = 0; //所有位初始化为0
        do  //尝试普通按钮的循环
        {
            initAllIsStoreAnswer();
            do  //尝试存储按钮各种方案的循环
            {
                tempResult = Game.startNum;  //每次按尝试一种存储方式都要重置结果变量
                for (int step = 0; step < stepsNum; step++)
                {
                    //判断是否存在store按钮
                    if (Game.storeOrNotAnswerListHead != NULL)
                    {
                        //根据存储按钮答案数组，决定是否存储
                        storeAnswer = Game.storeOrNotAnswerListHead->next;
                        //如果为真就存储长按
                        if(storeAnswer->isStoreAnswer[step])
                        {
                            storeNumberToButton(tempResult, storeAnswer->storeButtonP);
                        }
                    }
                    tempResult = pressButton(Game.buttons[answer[step]], tempResult);
                    //Output for debug...
                    if (isOutputSteps)
                        printSteps(answer, storeAnswer);
                    if (Game.isOnError == TRUE)
                    {
                        //已经计算出错，此方案不可行
                        break;
                    }
                }
                counter[0]++;  //尝试次数加一
                //判断是否成功
                if (tempResult == Game.gameAchieve && Game.isOnError == FALSE)
                {
                    printSolution(answer, stepsNum);
                    counter[1]++;
                    if (counter[1] >= 10)
                    {
                        resetButton();
                        goto findEnd;
                    }
                }
                else //本次尝试失败
                {
                    //重置错误状态
                    Game.isOnError = FALSE;
                }
                resetButton();
            } while(storeAnswer != NULL && !numerationAddOne(storeAnswer->isStoreAnswer, 2, stepsNum));
        } while (!numerationAddOne(answer, Game.buttonNum, stepsNum));
    }
    findEnd:
    free(answer); //释放
    return counter;
}

unsigned short isArithmeticButton(Button *button)
{
    unsigned short isTrue = FALSE;
    switch (button->type)
    {
        case PLUS:
            isTrue = TRUE;
            break;
        case MINUS:
            isTrue = TRUE;
            break;
        case MULTIPLY:
            isTrue = TRUE;
            break;
        case DIVIDE:
            isTrue = TRUE;
            break;
        default:
            break;
    }
    return isTrue;
}

unsigned short isModifiableButton(Button *button)
{
    unsigned short isTrue = FALSE;
    isTrue = isArithmeticButton(button);
    if (button->type == APPEND)
    {
        isTrue = TRUE;
    }
    return isTrue;
}

void modifyButtons(char operationChar, int operationNum)
{
    if (Game.isButtonModify == FALSE)
        backupButton();
    for (int i=0; i<Game.buttonNum; i++)
    {
        if (isModifiableButton(&Game.buttons[i]))
        {
            switch (operationChar)
            {
                case '+':
                    if (Game.buttons[i].type == APPEND)
                    {
                        Game.buttons[i].attachedInfo.appendNum += operationNum;
                    }
                    else
                    {
                        Game.buttons[i].attachedInfo.operationNum += operationNum;
                    }
                    break;
                case '-':
                    if (Game.buttons[i].type == APPEND)
                    {
                        Game.buttons[i].attachedInfo.appendNum -= operationNum;
                    }
                    else
                    {
                        Game.buttons[i].attachedInfo.operationNum -= operationNum;
                    }
                    break;
                case '*':
                    if (Game.buttons[i].type == APPEND)
                    {
                        Game.buttons[i].attachedInfo.appendNum *= operationNum;
                    }
                    else
                    {
                        Game.buttons[i].attachedInfo.operationNum *= operationNum;
                    }
                    break;
                case '/':
                    if (Game.buttons[i].type == APPEND)
                    {
                        Game.buttons[i].attachedInfo.appendNum /= operationNum;
                    }
                    else
                    {
                        Game.buttons[i].attachedInfo.operationNum /= operationNum;
                    }
                    break;
                default:break;
            }
        }
    }
}
