#ifndef __H_YRR_YARARA_H_
#define __H_YRR_YARARA_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <yrr-velocity.h>


typedef struct {
    int* points;
    size_t size;
    int* back;
    int* front;
    YrrVelocity vel;
} YrrYarara;

YrrYarara yrrNewYarara(size_t n) ;
void yrrFreeYarara(YrrYarara* y) ;
void yrrYararaPopFront(YrrYarara* yarara) ;
void yrrYararaPushBack(YrrYarara* yar, int x, int y) ;

#endif

