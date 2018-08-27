#ifndef _GAME_H_
#define _GAME_H_
#include "game.h"
#endif

int calculateNumberLength(int number);
int pressButton(Button buttonToPress, int currentNumber);
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix);
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth);
void solveIt();
int numberReplace(int number, int fromNum, int toNum);
int reverseNum(int number);