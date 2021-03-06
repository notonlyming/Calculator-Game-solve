#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

#include "game.h"

struct GameStruct *getGameLevelInfo(short isSilent);

Button analyseButtonStr(char *buttonStr);

int countBlankNum(char *strToCount, char charToFind);

char *strlwr(char *str);

char** split(char* strToSplit, char* splitChar);

int* getGameAchieve(int* achieveCount, short isSilent);

char *strrpc(char *str,char *oldstr,char *newstr);

void detectAndInsertDeleteButton(char* buttonAllStr);
void detectAndInsertReplaceButton(char* buttonAllStr);
void detectAndInsertRoundButton(char* buttonAllStr);
void detectCharAndConvertToNumber(char* achieveStr);
void detectAndInsertShiftButton(char* buttonAllStr);
void detectAndInsertInsertButton(char* buttonAllStr);
void detectAndInsertBitPlusOrMinusButton(char* buttonAllStr);
void detectABCButton(char* buttonAllStr);
void detectAndInsertLockButton(char* buttonAllStr);

int isNumberBit(char* p);
void appendLock(locker* lockP);

#endif