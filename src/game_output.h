#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include "game.h"

void printButtons(Button buttons[], int buttonNumber);
void printSolutionInfo(unsigned int counter[2], struct GameStruct *gameP);
void printWelcome();
void printSolution(unsigned short answer[], int stepsNum);

#endif