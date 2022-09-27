#ifndef __H_YRR_GAME_H_
#define __H_YRR_GAME_H_

#include <stdbool.h>
#include <yrr-media.h>
#include <yrr-board.h>
#include <yrr-title.h>


enum YrrGameState { YrrTitleState, YrrMenuState, YrrPlayState, YrrOptionsState, YrrGameOverState };

typedef struct YrrGame YrrGame;

typedef struct YrrGame {
    bool quit;
    YrrMedia* media;
    enum YrrGameState state;
    YrrBoard* board;
    void (*process_input)(YrrGame*);
    void (*update)(YrrGame*);
    void (*render)(YrrGame*);
    YrrTitle* title;
    int points;
} YrrGame;

void yrr_game_free(YrrGame* g);

void yrr_process_input(YrrGame* game) ;
void yrr_update(YrrGame* game) ;

void yrr_game_render(YrrGame* game) ;

void yrrGameTitleStateUpdate(YrrGame* g) ;
void yrrGameTitleStateProcessInput(YrrGame* game) ;

void yrrGamePlayStateUpdate(YrrGame* g) ;
#endif

