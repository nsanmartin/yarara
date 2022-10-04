#ifndef __H_YRR_YARARA_H_
#define __H_YRR_YARARA_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <yrr-velocity.h>
#include <yrr-point.h>

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
int yrrResetYarara(YrrYarara* yarara, YrrPoint first);

void yrrYararaPopFront(YrrYarara* yarara);
int yrrYararaPushBack(YrrYarara* yar, YrrPoint p);

YrrPoint yrrYararaGetBackToPoint(YrrYarara* y);
YrrPoint yrrYararaPlayStateUpdateHumanPlayer(YrrYarara* yr, const YrrBoard* b);

YrrPoint yrrYararaPlayStateUpdateAutomatePlayer(YrrYarara* yr, const YrrBoard* b);

bool yrrBoardBlockOccupiedByAnyYarara(const YrrBoard* board, YrrPoint p);
#endif

