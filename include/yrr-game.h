#ifndef __H_YRR_GAME_H_
#define __H_YRR_GAME_H_

#include <stdbool.h>

#include <yrr-point.h>
#include <yrr-util.h>

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
#endif

