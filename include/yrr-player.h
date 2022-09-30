#ifndef __H_YRR_PLAYER_H__
#define __H_YRR_PLAYER_H__

#include <stddef.h>

#include <yrr-yarara.h>

typedef struct {
    YrrYarara* yarara;
} YrrPlayer;

typedef struct {
    YrrPlayer* beg;
    size_t capacity;
    YrrPlayer* end;
} YrrVecPlayers;

YrrVecPlayers* yrrNewVecPlayers(YrrVecPoints* firsts);
#endif

