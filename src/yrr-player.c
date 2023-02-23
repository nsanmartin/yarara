#include <yrr-mem.h>
#include <yrr-player.h>

#include <yrr-yarara.h>
YrrPlayer* yrrNewPlayer(YrrPoint first) {
    YrrYarara* yarara = yrrNewYarara(1, first);
    if (!yarara) {
        return NULL;
    }

    YrrPlayer* rv = malloc(sizeof(YrrPlayer));
    if (!rv) {
        yrrFreeYarara(yarara);
        return NULL;
    }
    *rv = (YrrPlayer) { .yarara = yarara };
    return rv;
}

void yrrFreePlayer(YrrPlayer* player) {
    if (player) {
        yrrFreeYarara(player->yarara);
        free(player);
    }
}

YrrVecPlayers* yrrNewVecPlayers(YrrVecPoints firsts[static 1]) {
    size_t n = firsts->end - firsts->beg;
    YrrPlayer* data = malloc(n * sizeof(YrrPlayer));
    if (!data) {
        return NULL;
    }

    YrrVecPlayers* rv = malloc(sizeof(YrrVecPlayers));
    if (!rv) {
        free(data);
        return NULL;
    }

    rv->beg = data;
    rv->end = data;
    rv->capacity = n;

    for (YrrPoint* it = firsts->beg; it < firsts->end; ++it) {
        YrrYarara* yarara = yrrNewYarara(1, *it);

        if (!yarara) {
            for (;rv->beg < rv->end; ++rv->beg) { yrrFreeYarara(rv->beg->yarara); }
            free(data);
            free(rv);
            return NULL;
        }

        *rv->end++ = (YrrPlayer) {
            .yarara = yarara,
            .score = 0
        };
    }
    return rv;
}

void yrrFreeVecPlayers(YrrVecPlayers* ps) {
    if (ps) {
        for (YrrPlayer* it = ps->beg; it < ps->end; ++it) {
            yrrFreeYarara(it->yarara);
        }
        free(ps->beg);
        free(ps);
    }
}

int yrrResetPlayer(YrrPlayer player[static 1], YrrPoint first) {
    player->score = 0;
    int error = yrrResetYarara(player->yarara, first);
    return error;
}
