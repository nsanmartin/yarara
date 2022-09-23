#ifndef __H_YRR_BOARD_H_
#define __H_YRR_BOARD_H_

#include <yrr-yarara.h>

typedef struct {
    int x, y;
} YrrPoint;

typedef struct {
    int width;
    int height;
    YrrYarara yarara;
} YrrBoard;

#endif

