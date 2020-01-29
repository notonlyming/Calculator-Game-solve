#ifndef _GAME_PROCESS_H_
#define _GAME_PROCESS_H_

#include "game.h"
#include <stdio.h>

int calculateNumberLength(int number);

int pressButton(Button buttonToPress, int currentNumber);

int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix);

int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth);

unsigned int *solveIt(unsigned int counter[2], short isOutputSteps);

int numberReplace(int number, char *fromNumStr, char *toNumStr);

int reverseNum(int number);

int numberSum(int number);

int mirrorNumber(int number);

int checkNumberLarge(int number);

void modifyButtons(char operationChar, int operationNum);

void strReverse(char stringToReverse[]);

int numberAppend(int sourceNum, int numberToAppend);

void storeNumberToButton(int currentNumber, Button *storeButton);

storeOrNotAnswerStruct *createStoreAnswerListForStoreButton();

short initAllIsStoreAnswer();

unsigned short isArithmeticButton(Button *button);

unsigned short isModifiableButton(Button *button);

int lnv10(int number);

int powInt(int base, int exponent);

int sortNumber(int number, enum sort sortType);

int descendCmp(const void*, const void*);
int ascendCmp(const void*, const void*);

int deleteBit(int number, size_t bit);
int roundBit(int number, size_t roundBit);

int numberReplaceBit(int number, struct replaceBitInfo rplBitInfo);
int numberInsertBit(int number, struct insertBitInfo insertBitInfo);


#endif