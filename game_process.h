#ifndef _GAME_PROCESS_H_
#define _GAME_PROCESS_H_
#include "game.h"

int calculateNumberLength(int number);
int pressButton(Button buttonToPress, int currentNumber);
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix);
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth);
unsigned int* solveIt(unsigned int counter[2]);
int numberReplace(int number, int fromNum, int toNum);
int reverseNum(int number);
int numberSum(int number);
int mirrorNumber(int number);
int checkNumberLarge(int number);
void modifyButton(char operationChar, int operationNum);

#endif