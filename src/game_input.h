#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#include "game.h"

struct GameStruct *getGameLevelInfo();

Button analyseButtonStr(char *buttonStr);

int countBlankNum(char *strToCount, char charToFind);

char *strlwr(char *str);

char** split(char* strToSplit, char* splitChar);

int* getGameAchieve(int* achieveCount);

char *strrpc(char *str,char *oldstr,char *newstr);

void detectAndInsertDeleteButton(char* buttonAllStr);
void detectAndInsertReplaceButton(char* buttonAllStr);
void detectAndInsertRoundButton(char* buttonAllStr);

int isNumberBit(char* p);

#endif