#ifndef __H_YRR_YARARA_H_
#define __H_YRR_YARARA_H_

#include <stddef.h>
//#include <stdlib.h>
#include <string.h>
#include <yrr-velocity.h>
#include <yrr-point.h>
#include <yrr-util.h>
#include <yrr-board.h>

typedef struct YrrBoard YrrBoard;

typedef struct YrrYarara {
    YrrPoint* data;
    size_t size;
    YrrPoint* back;
    YrrPoint* front;
    YrrVelocity vel;
    YrrVelocity next_vel;
    int food;
    bool alive;
} YrrYarara;

YrrYarara* yrrNewYarara(size_t n, YrrPoint first);
void yrrFreeYarara(YrrYarara* y);
int yrrResetYarara(YrrYarara yarara[static 1], YrrPoint first);

void yrrYararaPopFront(YrrYarara yarara[static 1]);
int yrrYararaPushBack(YrrYarara yar[static 1], YrrPoint p);

YrrPoint yrrYararaGetBackToPoint(YrrYarara y[static 1]);
YrrResultPoint yrrYararaPlayStateUpdateHumanPlayer(YrrYarara yr[static 1], const YrrBoard b[static 1]);

YrrResultPoint yrrYararaPlayStateUpdateAutomatePlayer(YrrYarara yr[static 1], const YrrBoard b[static 1]);

bool yrrBoardBlockOccupiedByAnyYarara(const YrrBoard board[static 1], YrrPoint p);
#endif

