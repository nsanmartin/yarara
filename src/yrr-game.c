#include <yrr-game.h>

void yrr_game_free(YrrGame* g) {
    free(g->board->yarara.points);
    free(g->media->keyQueue.data);
}
