#ifndef __H_YRR_PLAYER_H__
#define __H_YRR_PLAYER_H__

#include <stddef.h>

#include <yrr-point.h>


typedef struct YrrYarara YrrYarara;

typedef struct {
    YrrYarara* yarara;
    int score;
} YrrPlayer;

typedef struct {
    YrrPlayer* beg;
    size_t capacity;
    YrrPlayer* end;
} YrrVecPlayers;

YrrVecPlayers* yrrNewVecPlayers(YrrVecPoints firsts[static 1]);
int yrrResetPlayer(YrrPlayer player[static 1], YrrPoint first);
void yrrFreeVecPlayers(YrrVecPlayers* ps);
#endif

