/*
 * 计算数字长度
 * 按下按钮
 * 位加一
 * 特定进制数加一
 * 数字子串替换
 * 反转数字
 * 数字按位求和
 */

#ifndef _STDIO_H_
#define _STDIO_H_
#include <stdio.h>
#endif

#ifndef _MATH_H_
#define _MATH_H_
#include <math.h>
#endif

#ifndef _STDLIB_H_
#define _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _GAME_H_
#define _GAME_H_
#include "game.h"
#endif

#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#endif

#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include "game_output.h"
#endif

#ifndef _GAME_PROCESS_H_
#define _GAME_PROCESS_H_
#include "game_process.h"
#endif

int reverseNum(int number)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number); //转成字符串
    //开始反转
    char tempChar;
    for (unsigned short index = 0; index < (strlen(numberStr) / 2); index++)
    {
        tempChar = numberStr[index];
        numberStr[index] = numberStr[strlen(numberStr) - 1 - index];
        numberStr[strlen(numberStr) - 1 - index] = tempChar;
    }
    sscanf(numberStr, "%d", &number); //转回数值
    //反转负值时带上负号
    if (numberStr[strlen(numberStr) - 1] == '-')
    {
        number *= -1;
    }
    return number;
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

//该函数将一个数字中的某部分替换成另外一部分，并返回替换后的数字
int numberReplace(int number, int fromNum, int toNum)
{
    char numberStr[NUMBER_STR_MAX_LENGTH] = {0},
         fromNumStr[NUMBER_STR_MAX_LENGTH] = {0},
         toNumStr[NUMBER_STR_MAX_LENGTH] = {0};
    char newNumStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    sprintf(fromNumStr, "%d", fromNum);
    sprintf(toNumStr, "%d", toNum);
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
            strP = endPosition;
        }
    }
    sscanf(newNumStr, "%d", &number); //转换为整型
    return number;
}

//左移或右移数字，返回移动后的数字
int shiftNumber(int number, char deraction)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    char newNumStr[NUMBER_STR_MAX_LENGTH];
    short sign = number>=0? +1 : -1;  //记录符号
    if (sign == 1)
    {
        sprintf(numberStr, "%d", number);  //取出
    }
    else
    {
        sprintf(numberStr, "%d", -number);  //取出
    }
    if (deraction == '>')
    {
        char tempChar;  //用于存储因向右移位被“挤”出来的字符
        tempChar = numberStr[strlen(numberStr)-1];
        numberStr[strlen(numberStr)-1] = '\0';
        sprintf(newNumStr, "%c%s", tempChar, numberStr);
    }
    else if(deraction == '<')
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
	short sign = number>=0 ? +1 : -1 ;
	if (number < 0)
	{
		number *= -1;
	}
	sprintf(numberStr, "%d", number);
	sprintf(reverseNumberStr, "%d", number);
    //开始反转
    char tempChar;
    for (unsigned short index = 0; index < (strlen(reverseNumberStr) / 2); index++)
    {
        tempChar = reverseNumberStr[index];
        reverseNumberStr[index] = reverseNumberStr[strlen(reverseNumberStr) - 1 - index];
        reverseNumberStr[strlen(reverseNumberStr) - 1 - index] = tempChar;
    }
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
            tempNum = numberStr[i] - '0';  //取出一位
            number += tempNum;
        }
    }
    else
    {
        for (unsigned int i=1; i<strlen(numberStr); i++)
        {
            tempNum = numberStr[i] - '0';  //取出一位
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
        if (result % *(buttonToPress.number) != 0)
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
    case POW:
        result = pow(result, *(buttonToPress.number) );
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
        result = shiftNumber(result, *(buttonToPress.number) );
		break;
	case MIRROR:
		result = mirrorNumber(result);
		break;
    case MODIFY:
        modifyButton(buttonToPress.number[0], buttonToPress.number[1]);
        break;
    case UNKNOW:; //do nothing
    break;
    }
	checkNumberLarge(result);
    return result;
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

//尝试所有可能，并返回由尝试次数和解的个数构成的数组地址，需要传入用于存储计数的数组
unsigned int* solveIt(unsigned int counter[2])
{
    int tempResult;                                                                                //试错临时结果变量
    unsigned short *answer = (unsigned short *)malloc(sizeof(unsigned short) * Game.allowMaxStep); //用于存储解的过程
    counter[0] = 0;  //尝试个数的计数器
    counter[1] = 0;  //求得解的个数计数器

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
                printSolution(answer, stepsNum);
                counter[1]++;
            }
            else //本次尝试失败
            {
                //重置错误状态
                Game.isOnError = FALSE;
            }
            counter[0]++;
            resetButton();
        } while (numerationAddOne(answer, Game.buttonNum, stepsNum) != -1);
    }
    free(answer); //释放
    return counter;
}

void modifyButton(char operationChar, int operationNum)
{
    if (Game.isButtonModify == FALSE)
        backupButton();
    for (int i=0; i<Game.buttonNum; i++)
    {
        if (Game.buttons[i].type == PLUS ||
            Game.buttons[i].type == MINUS ||
            Game.buttons[i].type == MULTIPLY ||
            Game.buttons[i].type == DIVIDE ||
            Game.buttons[i].type == APPEND)
        {
            switch (operationChar)
            {
                case '+':
                    Game.buttons[i].number[0] += operationNum;
                    break;
                case '-':
                    Game.buttons[i].number[0] -= operationNum;
                    break;
                case '*':
                    Game.buttons[i].number[0] *= operationNum;
                    break;
                case '/':
                    Game.buttons[i].number[0] /= operationNum;
                    break;
            }
        }
    }
}
