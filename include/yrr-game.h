#ifndef __H_YRR_GAME_H_
#define __H_YRR_GAME_H_

#include <stdbool.h>
#include <yrr-media.h>


enum YrrGameState { YrrTitleState, YrrMenuState, YrrPlayState, OptionsState };

typedef struct {
    bool quit;
    YrrMedia* media;
    enum YrrGameState state;
} YrrGame;


void yrr_process_input(YrrGame* game) ;
void yrr_update(YrrGame* game) ;
void yrr_render(YrrGame* game) ;

#endif

