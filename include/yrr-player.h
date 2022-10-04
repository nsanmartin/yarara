#ifndef __H_YRR_PLAYER_H__
#define __H_YRR_PLAYER_H__

#include <stddef.h>

#include <yrr-yarara.h>

typedef struct {
    YrrYarara* yarara;
    int score;
} YrrPlayer;

typedef struct {
    YrrPlayer* beg;
    size_t capacity;
    YrrPlayer* end;
} YrrVecPlayers;

YrrVecPlayers* yrrNewVecPlayers(YrrVecPoints* firsts);
int yrrResetPlayer(YrrPlayer* player, YrrPoint first);
#endif

