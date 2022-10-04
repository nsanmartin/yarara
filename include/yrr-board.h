#ifndef __H_YRR_BOARD_H_
#define __H_YRR_BOARD_H_

#include <yrr-point.h>
#include <yrr-yarara.h>
#include <yrr-player.h>

typedef struct {
    YrrPoint food;
} YrrLevel;

typedef struct YrrBoard {
    int width;
    int height;
    YrrVecPlayers* players;
    YrrLevel level;
} YrrBoard;


YrrBoard* yrrNewBoard(YrrPoint sz);
void yrrFreeBoard(YrrBoard* board);
int yrrResetBoard(YrrBoard* board);
#endif

