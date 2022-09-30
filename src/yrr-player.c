#include <yrr-player.h>

#include <yrr-yarara.h>
YrrPlayer* yrrNewPlayer(YrrPoint first) {
    YrrYarara* yarara = yrrNewYarara(1, first);
    if (!yarara) {
        return NULL;
    }

    YrrPlayer* rv = malloc(sizeof(YrrPlayer));
    if (!rv) {
        return NULL;
    }
    *rv = (YrrPlayer) { .yarara = yarara };
    return rv;
}

void yrrFreePlayer(YrrPlayer* player) {
    yrrFreeYarara(player->yarara);
    free(player);
}

YrrVecPlayers* yrrNewVecPlayers(YrrVecPoints* firsts) {
    size_t n = firsts->end - firsts->beg;
    YrrPlayer* data = malloc(n * sizeof(YrrPlayer));
    if (!data) {
        return NULL;
    }

    YrrVecPlayers* rv = malloc(sizeof(YrrVecPlayers));
    if (!rv) {
        return NULL;
    }

    rv->beg = data;
    rv->end = data;
    rv->capacity = n;

    for (YrrPoint* it = firsts->beg; it < firsts->end; ++it) {
        YrrYarara* yarara = yrrNewYarara(1, *it);
        if (!yarara) {
            return NULL;
        }
        *rv->end++ = (YrrPlayer) {
            .yarara = yarara,
            .score = 0
        };
    }
    return rv;
}

void yrrResetPlayer(YrrPlayer* player, YrrPoint first) {
    yrrResetYarara(player->yarara, first);
    player->score = 0;
}
