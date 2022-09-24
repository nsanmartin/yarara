#include <yrr-game.h>
#include <yrr-media.h>

#include <stdio.h>
void yrrGameTitleStateUpdate(YrrGame* g) {
    ++g->title->offset.x;
    ++g->title->offset.y;
}

void yrrGamePlayStateReadInput(YrrGame* g) {
    YrrKeyQueue* q = &g->media->keyQueue;
    YrrYarara* yr = &g->board->yarara;
    while (!yrrKeyQueueIsEmpty(q)) {
        YrrKey k = yrrKeyQueuePopFront(q);
        switch (k) {
            case YrrK_Left:
                yr->vel.x = -1;
                yr->vel.y = 0;
                break;
            case YrrK_Right:
                yr->vel.x = 1;
                yr->vel.y = 0;
                break;
            case YrrK_Up:
                yr->vel.x = 0;
                yr->vel.y = -1;
                break;
            case YrrK_Down:
                yr->vel.x = 0;
                yr->vel.y = 1;
                break;
            default:
                // do nothing
                break;
        }
    }
}

void yrrGamePlayStateUpdate(YrrGame* game) {

    yrrGamePlayStateReadInput(game) ;
    YrrYarara yr = game->board->yarara;
    YrrVelocity v = yr.vel;

    for (int* it = yr.front; it < yr.back; it += 2) {
        it[0] = (it[0] + v.x) % game->board->width;
        it[1] = (it[1] + v.y) % game->board->height;
    }
}

