#include <yrr-game.h>

void yrr_game_free(YrrGame* g) {
    free(g->board->yarara.data);
    free(g->media->keyQueue.data);
}
