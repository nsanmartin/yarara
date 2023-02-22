#ifndef __H_YRR_GAME_H_
#define __H_YRR_GAME_H_

#include <stdbool.h>

#include <yrr-point.h>
#include <yrr-util.h>
#include <yrr-board.h>
#include <yrr-media.h>

typedef struct YrrMedia YrrMedia;
typedef struct YrrBoard YrrBoard;
typedef struct YrrTitle YrrTitle;


typedef enum {
    YrrStateTitle, YrrStateMenu, YrrStatePlay, YrrStateOptions, YrrStateGameOver
} YrrGameState ;

typedef struct YrrGame YrrGame;

typedef struct YrrGame {
    bool quit;
    YrrMedia* media;
    YrrGameState state;
    YrrBoard* board;
    void (*process_input)(YrrGame*);
    void (*update)(YrrGame*);
    void (*render)(YrrGame*);
    YrrTitle* title;
    int points;
} YrrGame;

YrrGame* yrrNewGame(YrrPoint win_sz, YrrPoint board_sz);
void yrrFreeGame(YrrGame* game);

int yrrResetGame(YrrGame* game);
char* yrrGameGetWinner(YrrGame* g);

inline static int yrrGameGetBlockWidth(const YrrGame* g) {
    return  g->media->windowWidth / g->board->width; 
}

inline static int yrrGameGetBlockHeight(const YrrGame* g) {
    return   g->media->windowHeight / g->board->height; 
}
#endif

