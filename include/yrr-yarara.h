#ifndef __H_YRR_YARARA_H_
#define __H_YRR_YARARA_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <yrr-velocity.h>
#include <yrr-point.h>
#include <yrr-point.h>


typedef struct {
    YrrPoint* data;
    size_t size;
    YrrPoint* back;
    YrrPoint* front;
    YrrVelocity vel;
    int food;
} YrrYarara;

YrrYarara yrrNewYarara(size_t n) ;
void yrrFreeYarara(YrrYarara* y) ;
void yrrYararaPopFront(YrrYarara* yarara) ;
void yrrYararaPushBack(YrrYarara* yar, int x, int y) ;

bool yrrYararaGetsHitByBlock(YrrYarara* yr, YrrPoint p) ;
YrrPoint yrrYararaGetBackToPoint(YrrYarara* y) ;
#endif

