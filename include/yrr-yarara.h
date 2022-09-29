#ifndef __H_YRR_YARARA_H_
#define __H_YRR_YARARA_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <yrr-velocity.h>
#include <yrr-point.h>

typedef struct YrrBoard YrrBoard;

typedef struct {
    YrrPoint* data;
    size_t size;
    YrrPoint* back;
    YrrPoint* front;
    YrrVelocity vel;
    YrrVelocity next_vel;
    int food;
    bool alive;
} YrrYarara;

YrrYarara yrrNewYarara(size_t n);
void yrrFreeYarara(YrrYarara* y);
void yrrYararaPopFront(YrrYarara* yarara);
void yrrYararaPushBack(YrrYarara* yar, YrrPoint p);

bool yrrYararaGetsHitByBlock(YrrYarara* yr, YrrPoint p);
YrrPoint yrrYararaGetBackToPoint(YrrYarara* y);
// YrrPoint yrrYararaNextPoint(YrrYarara* yr, int maxx, int maxy);
YrrPoint yrrYararaPlayStateUpdateHumanPlayer(YrrYarara* yr, const YrrBoard* b);

YrrPoint yrrYararaPlayStateUpdateAutomatePlayer(YrrYarara* yr, const YrrBoard* b);
#endif

