#ifndef __H_YRR_GAME_H_
#define __H_YRR_GAME_H_

#include <stdbool.h>
#include <yrr-media.h>
#include <yrr-board.h>
#include <yrr-title.h>


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

void yrrResetGame(YrrGame* game);
void yrr_process_input(YrrGame* game) ;
void yrr_update(YrrGame* game) ;

void yrr_game_render(YrrGame* game) ;

void yrrGameTitleStateUpdate(YrrGame* g) ;
void yrrGameTitleStateProcessInput(YrrGame* game) ;

void yrrGamePlayStateUpdate(YrrGame* g) ;

void yrrChangeStateMethods(YrrGame* game, YrrGameState new_state);
#endif

