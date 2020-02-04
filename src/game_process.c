/*
 * 处理游戏的各种操作，计算关卡的可用解
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <string.h>
#include "game_output.h"
#include "game_input.h"
#include "game_process.h"
#include "stepObserver.h"

int reverseNum(int number) {
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number); //转成字符串
    strReverse(numberStr);
    sscanf(numberStr, "%d", &number); //转回数值
    //反转负值时带上负号
    if (numberStr[strlen(numberStr) - 1] == '-') {
        number *= -1;
    }
    return number;
}

//反转字符串
void strReverse(char stringToReverse[]) {
    //开始反转
    char tempChar;
    for (unsigned short index = 0; index < (strlen(stringToReverse) / 2); index++) {
        tempChar = stringToReverse[index];
        stringToReverse[index] = stringToReverse[strlen(stringToReverse) - 1 - index];
        stringToReverse[strlen(stringToReverse) - 1 - index] = tempChar;
    }
}

int calculateNumberLength(int number) {
    if (number == 0) {
        return 1;
    } else {
        if (number < 0) {
            number *= -1;
        }
        int count = 0;
        while (number > 0) {
            number /= 10;
            count++;
        }
        return count;
    }
}

//该函数将一个数字中的某部分替换成另外一部分，并返回替换后的数字
int numberReplace(int number, char *fromNumStr, char *toNumStr) {
    char numberStr[NUMBER_STR_MAX_LENGTH] = {0};
    sprintf(numberStr, "%d", number);
    strrpc(numberStr, fromNumStr, toNumStr);
    sscanf(numberStr, "%d", &number); //转换为整型
    return number;
}

//左移或右移数字，返回移动后的数字
int shiftNumber(int number, enum direction direction) {
    char numberStr[NUMBER_STR_MAX_LENGTH];
    char newNumStr[NUMBER_STR_MAX_LENGTH];
    short sign = (short) (number >= 0 ? +1 : -1);  //记录符号
    if (sign == 1) {
        sprintf(numberStr, "%d", number);  //取出
    } else {
        sprintf(numberStr, "%d", -number);  //取出
    }
    if (direction == SHIFT_RIGHT) {
        char tempChar;  //用于存储因向右移位被“挤”出来的字符
        tempChar = numberStr[strlen(numberStr) - 1];
        numberStr[strlen(numberStr) - 1] = '\0';
        sprintf(newNumStr, "%c%s", tempChar, numberStr);
    } else if (direction == SHIFT_LEFT) {
        sprintf(newNumStr, "%s%c", numberStr + 1, numberStr[0]);
    } else {
        Game.isOnError = TRUE;
    }
    sscanf(newNumStr, "%d", &number); //转换为整型
    return number * sign;
}

//mirror number, return ok number
int mirrorNumber(int number) {
    char numberStr[NUMBER_STR_MAX_LENGTH];
    char reverseNumberStr[NUMBER_STR_MAX_LENGTH];
    short sign = (short) (number >= 0 ? +1 : -1);
    if (number < 0) {
        number *= -1;
    }
    sprintf(numberStr, "%d", number);
    sprintf(reverseNumberStr, "%d", number);
    strReverse(reverseNumberStr);
    strcat(numberStr, reverseNumberStr);
    sscanf(numberStr, "%d", &number); //转换为整型
    return number * sign;
}

int cutNumber(int number, char* cutNum)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    strrpc(numberStr, cutNum, "");
    sscanf(numberStr, "%d", &number);
    return number;
}

//求每一位数字的和并返回求和后的数字,这里假设求和的数字必须是正的
int numberSum(int number) {
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);  //取出
    unsigned short tempNum;
    number = 0;  //结果先初始化为0
    if (numberStr[0] != '-') {
        for (unsigned int i = 0; i < strlen(numberStr); i++) {
            tempNum = (unsigned short) (numberStr[i] - '0');  //取出一位
            number += tempNum;
        }
    } else {
        for (unsigned int i = 1; i < strlen(numberStr); i++) {
            tempNum = (unsigned short) (numberStr[i] - '0');  //取出一位
            number += tempNum;
        }
        number *= -1;
    }
    return number;
}

//此处声明qsort所用的比较器函数
int descendCmp(const void *number1, const void *number2){
    short a = *(short*)number1;
    short b = *(short*)number2;
    return a - b;
}

int ascendCmp(const void *number1, const void *number2){
    short a = *(short*)number1;
    short b = *(short*)number2;
    return b - a;
}

int sortNumber(int number, enum sort sortType){
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);   //转为字符串
    int numberLen = strlen(numberStr);
    short numberArray[numberLen];
    //提取字符串中的数字到数字数组中
    for(int i=0; numberStr[i] != '\0'; i++){
        numberArray[i] = numberStr[i] - 48;
    }
    if (sortType == SORT_DESCENDING)
    {
        qsort(numberArray, numberLen, sizeof(short), descendCmp);
    }
    else
    {
        qsort(numberArray, numberLen, sizeof(short), ascendCmp);
    }
    // 将数字数组乘以位权并相加
    int result = 0;
    for(int i=0; i < numberLen; i++){
        result += numberArray[i] * powInt(10, i);
    }
    return result;
}

int pressButton(Button buttonToPress, int currentNumber) {
    int result = currentNumber;
    switch (buttonToPress.type) {
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
            //是否产生小数判断
            if (result % buttonToPress.attachedInfo.operationNum != 0) {
                Game.isOnError = TRUE;
            } else {
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
            result = numberReplace(result, buttonToPress.attachedInfo.replaceInfo.strReplaceFrom,
                                   buttonToPress.attachedInfo.replaceInfo.strReplaceTo);
            break;
        case POW:
            result = (int) powInt(result, buttonToPress.attachedInfo.exponent);
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
        case SHIFT_TIMES:
            for (int i = 0; i < buttonToPress.attachedInfo.shiftTimes; i++)
            {
                result = shiftNumber(result, SHIFT_LEFT);
            }
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
        case SORT:
            result = sortNumber(result, buttonToPress.attachedInfo.sortType);
            break;
        case CUT:
            result = cutNumber(result, buttonToPress.attachedInfo.cutNum);
            break;
        case DELETE:
            result = deleteBit(result, buttonToPress.attachedInfo.deleteBit);
            break;
        case ROUND:
            result = roundBit(result, buttonToPress.attachedInfo.roundBit);
            break;
        case REPLACE_BIT:
            result = numberReplaceBit(result, buttonToPress.attachedInfo.rplBitInfo);
            break;
        case INSERT:
            result = numberInsertBit(result, buttonToPress.attachedInfo.insertBitInfo);
            break;
        case BIT_PLUS:
            result = plusBit(result, buttonToPress.attachedInfo.plusBitInfo);
            break;
        case UNKNOW:; //do nothing
            break;
    }
    checkNumberLarge(result);
    int before = result;
    if (Game.portalPointer) {
        while(1)
        {
            result = doTransmit(*Game.portalPointer, result);
            if (result != before)
            {
                before = result;
            }
            else
            {
                break;
            }
        }
    }
    return result;
}

// 按位加
int plusBit(int number, struct plusBitInfo plusBitInfo)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    if(plusBitInfo.plusBit <= strlen(numberStr) + 1 && plusBitInfo.plusBit >= 1)
    {
        unsigned short digit = numberStr[plusBitInfo.plusBit - 1] - 48;
        digit += plusBitInfo.plusNumberChar - 48;
        digit %= 10;
        numberStr[plusBitInfo.plusBit - 1] = digit + 48;
        sscanf(numberStr, "%d", &number);
    }
    else
    {
        Game.isOnError = TRUE;
    }
    return number;
}

int numberInsertBit(int number, struct insertBitInfo insertBitInfo)
{
    //先劈开再拼接以实现插入！
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    if(insertBitInfo.insertBit <= strlen(numberStr) + 1 && insertBitInfo.insertBit >= 1)
    {
        char before[NUMBER_STR_MAX_LENGTH];
        char after[NUMBER_STR_MAX_LENGTH];
        // 这里减二一个是从零开始减一，另一个是在前面插入，减一。
        int insertBitIndex = insertBitInfo.insertBit - 2;
        for(int i = 0; i <= insertBitIndex; i++)
        {
            before[i] = numberStr[i];
        }
        before[insertBitIndex + 1] = insertBitInfo.insertNumberChar;
        before[insertBitIndex + 2] = '\0';
        strcpy(after, numberStr + insertBitIndex + 1);
        strcat(before, after);
        sscanf(before, "%d", &number);
    }
    else
    {
        Game.isOnError = TRUE;
    }
    return number;
}

int numberReplaceBit(int number, struct replaceBitInfo rplBitInfo)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    size_t numberStrLen = strlen(numberStr);
    // 如果传入的位数不对，则无效讲出错设置为true
    if(rplBitInfo.replaceBit <= numberStrLen && rplBitInfo.replaceBit > 0)
    {
        numberStr[rplBitInfo.replaceBit - 1] = rplBitInfo.replaceNumberChar;
        sscanf(numberStr, "%d", &number);
    }
    else
    {
        Game.isOnError = TRUE;
    }
    return number;
}

int roundBit(int number, size_t roundBit)
{
    char numberStr[NUMBER_STR_MAX_LENGTH];
    sprintf(numberStr, "%d", number);
    size_t numberStrLen = strlen(numberStr);
    // 仅当传入的要round的位不是最后一位且不超过总位数时才执行操作
    if (roundBit < numberStrLen && roundBit > 0)
    {
        // 往前读一位
        char bit = numberStr[roundBit];
        if (bit > '4') numberStr[roundBit - 1] += 1;
        // 从round前面的一位开始，一直到最后一位，全部置零。
        for (size_t i = roundBit; i < numberStrLen; i++)
        {
            numberStr[i] = '0';
        }
        sscanf(numberStr, "%d", &number);
    }
    else
    {
        Game.isOnError = TRUE;
    }
    
    return number;
}

// 删除指定位的数字
// 如果传入bit不对，则置为游戏出错，重新计算
int deleteBit(int number, size_t bit)
{
    char numberStr[MAX_BIT];
    sprintf(numberStr, "%d", number);
    size_t numberStrLen = strlen(numberStr);
    if(bit <= numberStrLen && bit > 0)
    {
        numberStr[bit - 1] = ' ';
        strrpc(numberStr, " ", "");
        sscanf(numberStr, "%d", &number);
    }
    else
    {
        Game.isOnError = TRUE;
    }
    return number;
}

int lnv10(int number) {
    short sign;
    if (number >= 0) {
        sign = (short) +1;
    } else {
        sign = (short) -1;
        number *= -1;
    }
    short numberLength = (short) calculateNumberLength(number);
    short *numberBit = (short*) malloc(numberLength * sizeof(short));
    //取出每一位
    for (int i = 0; i < numberLength; i++) {
        numberBit[i] = (short) (number % 10);
        number /= 10;
        numberBit[i] = (short) ((10 - numberBit[i]) % 10); //用10减去它
    }
    //放回每一位
    for (int i = 0; i < numberLength; i++) {
        number += (int) numberBit[i] * powInt(10, i);
    }
    free(numberBit);
    return number * sign;
}

int powInt(int base, int exponent)
{
    int result = 1;
    for (int i=0; i<exponent; i++)
    {
        result *= base;
    }
    return result;
}

//这里处理长按
void storeNumberToButton(int currentNumber, Button *storeButton) {
    if (Game.isButtonModify == FALSE) {
        backupButton();
    }
    if (currentNumber >= 0) {
        storeButton->attachedInfo.storeNum = currentNumber;
    } else {
        Game.isOnError = TRUE;
    }
}

int numberAppend(int sourceNum, int numberToAppend) {
    if (sourceNum >= 0)
        sourceNum = (int) (sourceNum * powInt(10, calculateNumberLength(numberToAppend)) + numberToAppend);
    else
        sourceNum = (int) (sourceNum * powInt(10, calculateNumberLength(numberToAppend)) - numberToAppend);
    return sourceNum;
}

//检查结果的数字是否超过6位，如果超过，game.error为真，该方案无效
int checkNumberLarge(int number) {
    if (number > 999999 || number < -99999) {
        Game.isOnError = TRUE;
    }
    return number;
}

//有必要写一个为某一进制位加一的函数减轻复杂度,直接加1返回0，发生进位返回-1
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix) {
    if (number[witchBit] + 1 != radix) {
        number[witchBit] += 1;
        return 0;
    } else {
        //发生进位
        number[witchBit] = 0;
        return -1;
    }
}

//该函数用于实现特定的进制数加1，多少进制的数用来表示那个按钮按下，当进制数溢出，返回-1，即为所有情况试错完成，否则返回0
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth) {
    unsigned short witchBit;
    for (witchBit = 0; witchBit < numberWidth; witchBit++) {
        if (bitAdd(number, witchBit, radix) == 0) {
            //位加1成功且未发生进位
            break;
        } else {
            //位加1成功，发生进位
            if (witchBit == numberWidth - 1) {
                //已经"溢出"，恢复状态
                number[witchBit] = (unsigned short) (radix - 1);
                return -1;
            } else {
                //未溢出，继续给高位加一
                continue;
            }
        }
    }
    //加一操作顺利结束，未发生数满溢出
    return 0;
}

storeOrNotAnswerStruct *createStoreAnswerListForStoreButton() {
    //计算存储按钮的个数
    short storeButtonIndex = -1;  //记录按钮的索引信息，方便后面添加该按钮到存储方案链表里
    for (short i = 0; i < Game.buttonNum; i++) {
        if (Game.buttons[i].type == STORE) {
            storeButtonIndex = i;  //记录索引信息
            break;
        }
    }
    if (storeButtonIndex != -1) {
        //申请空间
        Game.storeOrNotAnswerStructP = (storeOrNotAnswerStruct *) malloc(sizeof(storeOrNotAnswerStruct));
        //为新添加的节点指明它对应的是哪个按钮的存储方案
        Game.storeOrNotAnswerStructP->storeButtonP = &(Game.buttons[storeButtonIndex]);
        //创建插空法存储方案数组
        Game.storeOrNotAnswerStructP->isStoreAnswer = malloc(
                sizeof(Game.storeOrNotAnswerStructP->isStoreAnswer[0]) * Game.allowMaxStep);
        //数组元素初始化为0表示不按
        for (int j = 0; j < Game.allowMaxStep; j++) {
            Game.storeOrNotAnswerStructP->isStoreAnswer[j] = 0;
        }
    }
    return Game.storeOrNotAnswerStructP;
}

short initAllIsStoreAnswer() {
    if (Game.storeOrNotAnswerStructP) {
        if (Game.storeOrNotAnswerStructP) {
            for (int i = 0; i < Game.allowMaxStep; i++)
                Game.storeOrNotAnswerStructP->isStoreAnswer[i] = 0; //所有位初始化为0
        }
        return 0;
    } else {
        return -1;
    }
}

//尝试所有可能，并返回由尝试次数和解的个数构成的数组地址，需要传入用于存储计数的数组
unsigned int *solveIt(unsigned int counter[2], short isOutputSteps, short isSilent) {
    int tempResult;    //试错临时结果变量
    unsigned short *answer = (unsigned short *) malloc(sizeof(unsigned short) * Game.allowMaxStep); //用于存储解的过程
    counter[0] = 0;  //尝试个数的计数器
    counter[1] = 0;  //求得解的个数计数器

    //从最少的步数开始尝试，看看有没有最优解
    storeOrNotAnswerStruct *storeAnswer = createStoreAnswerListForStoreButton();  //存储当前尝试的store答案数组指针
    // 先看看是不是不用计算就有结果
    counter[0]++; counter[1]++;
    if (Game.startNum == Game.gameAchieve)
    {
        if (Game.hasABC)
        {
            printf("发现解(1步) (ABC) 结果：%d  \n", Game.startNum);
        }
        else
        {
            printf("发现解(0步) 结果：%d  \n", Game.startNum);
        }
    }
    
    for (unsigned short stepsNum = 1; stepsNum <= Game.allowMaxStep; stepsNum++) {
        for (int i = 0; i < Game.allowMaxStep; i++)
            answer[i] = 0; //所有位初始化为0
        do  //尝试普通按钮的循环
        {
            initAllIsStoreAnswer();
            do  //尝试存储按钮各种方案的循环
            {
                tempResult = Game.startNum;  //每次按尝试一种存储方式都要重置结果变量
                for (int step = 0; step < stepsNum; step++) {
                    // 更新，store按钮也算步数，加起来超步数将break并置为error
                    if (storeAnswer && stepsNum + countOnes(storeAnswer->isStoreAnswer, stepsNum) > Game.allowMaxStep)
                    {
                        Game.isOnError = TRUE;
                        break;
                    }
                    
                    //判断是否存在store按钮
                    if (storeAnswer) {
                        //根据存储按钮答案数组，决定是否存储
                        //如果为真就存储长按
                        if (storeAnswer->isStoreAnswer[step]) {
                            storeNumberToButton(tempResult, storeAnswer->storeButtonP);
                        }
                    }
                    tempResult = pressButton(Game.buttons[answer[step]], tempResult);
                    //Output for debug...
                    if (isOutputSteps)
                        printSteps(answer, storeAnswer);
                    if (Game.isOnError == TRUE) {
                        //已经计算出错，此方案不可行
                        break;
                    }
                }
                counter[0]++;  //尝试次数加一
                //判断是否成功
                if (tempResult == Game.gameAchieve && Game.isOnError == FALSE) {
                    printSolution(answer, stepsNum);
                    counter[1]++;
                    if (counter[1] == 10 && !isSilent) {
                        char isCalculateAllSolve;
                        printf("该level可能有10个以上的解...\n"
                               "继续计算可能需要消耗大量时间，是否继续？(y/n):");
                        scanf("%c", &isCalculateAllSolve);
						getchar();  //拿掉换行符
                        if (isCalculateAllSolve == 'n') {
                            resetButton();
                            goto findEnd;
                        }
                    }
                } else {
                    //本次尝试失败
                    //重置错误状态
                    Game.isOnError = FALSE;
                }
                resetButton();
            } while (storeAnswer != NULL && !numerationAddOne(storeAnswer->isStoreAnswer, 2, stepsNum));
        } while (!numerationAddOne(answer, Game.buttonNum, stepsNum));
    }
    findEnd:
    free(answer); //释放
    return counter;
}

unsigned short isArithmeticButton(Button *button) {
    unsigned short isTrue = FALSE;
    switch (button->type) {
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

unsigned short isModifiableButton(Button *button) {
    unsigned short isTrue = FALSE;
    isTrue = isArithmeticButton(button);
    if (button->type == APPEND) {
        isTrue = TRUE;
    }
    return isTrue;
}

void modifyButtons(char operationChar, int operationNum) {
    if (Game.isButtonModify == FALSE)
        backupButton();
    for (int i = 0; i < Game.buttonNum; i++) {
        if (isModifiableButton(&Game.buttons[i])) {
            switch (operationChar) {
                case '+':
                    if (Game.buttons[i].type == APPEND) {
                        Game.buttons[i].attachedInfo.appendNum += operationNum;
                    } else {
                        Game.buttons[i].attachedInfo.operationNum += operationNum;
                    }
                    break;
                case '-':
                    if (Game.buttons[i].type == APPEND) {
                        Game.buttons[i].attachedInfo.appendNum -= operationNum;
                    } else {
                        Game.buttons[i].attachedInfo.operationNum -= operationNum;
                    }
                    break;
                case '*':
                    if (Game.buttons[i].type == APPEND) {
                        Game.buttons[i].attachedInfo.appendNum *= operationNum;
                    } else {
                        Game.buttons[i].attachedInfo.operationNum *= operationNum;
                    }
                    break;
                case '/':
                    if (Game.buttons[i].type == APPEND) {
                        Game.buttons[i].attachedInfo.appendNum /= operationNum;
                    } else {
                        Game.buttons[i].attachedInfo.operationNum /= operationNum;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
