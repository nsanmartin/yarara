#ifndef __H_YRR_BOARD_H_
#define __H_YRR_BOARD_H_

#include <yrr-point.h>
#include <yrr-player.h>
#include <SDL.h>

typedef struct {
    YrrPoint food;
} YrrLevel;

typedef struct YrrBoard {
    YrrPoint offset;
    // the number of block the board has is width * height
    int width;
    int height;
    YrrVecPlayers* players;
    YrrLevel level;
} YrrBoard;


YrrBoard* yrrNewBoard(YrrPoint sz);
void yrrFreeBoard(YrrBoard* board);
int yrrResetBoard(YrrBoard board[static 1]);

static inline void yrrBoardApplyOffset(YrrBoard b[static 1], SDL_Rect r[static 1]) {
    r->x += b->offset.x;
    r->y += b->offset.y;
}
#endif

