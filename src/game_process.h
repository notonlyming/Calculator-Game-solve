#ifndef _GAME_PROCESS_H_
#define _GAME_PROCESS_H_
#include "game.h"

int calculateNumberLength(int number);
int pressButton(Button buttonToPress, int currentNumber);
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix);
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth);
unsigned int* solveIt(unsigned int counter[2], short isOutputSteps);
int numberReplace(int number, char *fromNumStr, char *toNumStr);
int reverseNum(int number);
int numberSum(int number);
int mirrorNumber(int number);
int checkNumberLarge(int number);
void modifyButtons(char operationChar, int operationNum);
void strReverse(char stringToReverse[]);
int numberAppend(int sourceNum, int numberToAppend);
void storeNumberToButton(int currentNumber, Button *storeButton);
storeOrNotAnswerStruct* createStoreAnswerListForStoreButton();
short initAllIsStoreAnswer();
unsigned short isArithmeticButton(Button *button);
unsigned short isModifiableButton(Button *button);
int lnv10(int number);

#endif