#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_
#include "game.h"

struct GameStruct* getGameLevelInfo();
Button analyseButtonStr(char *buttonStr);
int countBlankNum(char *strTocount);
char *strlwr(char *str);

#endif