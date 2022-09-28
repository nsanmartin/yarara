#ifndef __H_YRR_BOARD_H_
#define __H_YRR_BOARD_H_

#include <yrr-point.h>
#include <yrr-yarara.h>

typedef struct {
    YrrPoint food;
} YrrLevel;

typedef struct YrrBoard {
    int width;
    int height;
    YrrYarara yarara;
    YrrLevel level;
} YrrBoard;


#endif

