#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#include "game.h"

struct GameStruct *getGameLevelInfo();

Button analyseButtonStr(char *buttonStr);

int countBlankNum(char *strToCount, char);

char *strlwr(char *str);

char** split(char* strToSplit, char* splitChar);

int* getGameAchieve(int* achieveCount);

#endif