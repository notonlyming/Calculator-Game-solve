#ifndef CALCULATOR_GAME_SOLVE_PORTAL_H
#define CALCULATOR_GAME_SOLVE_PORTAL_H

#define PORTAL_HAS_NUMBER 1
#define PORTAL_NO_NUMBER 0

typedef struct {
    int portalEntranceIndex;
    int portalExitIndex;
} portal;

int checkPortalStatus(portal portalToCheck, int currentNumber);

int doTransmit(portal portalToDoTransmit, int currentNumber);

void getAndInitialisePortal(short isSilent);

#endif //CALCULATOR_GAME_SOLVE_PORTAL_H
