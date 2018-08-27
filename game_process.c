/*
 * 计算数字长度
 * 按下按钮
 * 位加一
 * 特定进制数加一
 * 数字子串替换
 * 反转数字
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

//该函数将一个数字中的某部分替换乘另外一部分，并返回替换后的数字
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
    case SQUARE:
        result = result * result;
        break;
    case SIGN_CONVERT:
        result *= -1;
        break;
    case REVERSE:
        result = reverseNum(result);
        break;
    case UNKNOW:; //do nothing
        break;
    }
    return result;
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