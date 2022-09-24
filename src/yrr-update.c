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

int yrrGameNextX(YrrGame* game, int x) {
    return (x + game->board->yarara.vel.x + game->board->width) % game->board->width;
}

int yrrGameNextY(YrrGame* game, int y) {
    return (y + game->board->yarara.vel.y + game->board->height) % game->board->height;
}

YrrPoint yrrGameNextPoint(YrrGame* g, YrrPoint p) {
    p.x = yrrGameNextX(g, p.x);
    p.y = yrrGameNextY(g, p.y);
    return p;
}

void yrrGamePlayStateUpdate(YrrGame* game) {

    yrrGamePlayStateReadInput(game) ;
    YrrYarara* yr = &game->board->yarara;

    YrrPoint next = yrrGameNextPoint(game, yrrYararaGetBackToPoint(yr));
    YrrPoint food = game->board->level.food;


    if (yrr_point_eq(next, food)) {

        yrrYararaPushBack(yr, next.x, next.y);
        
        YrrPoint p = game->board->level.food;
        p.x = ((p.x + 1) * 71) % game->board->width;
        p.y = ((p.y - 1) * 371) % game->board->height;
        game->board->level.food = p;
        printf("food x: %d, y: %d, w: %d h: %d\n", p.x, p.y,  game->board->width, game->board->height);

    } else {
        yrrYararaPushBack(yr, next.x, next.y);
        yrrYararaPopFront(yr);
            //for (int* it = yr->front; it < yr->back; it += 2) {
        //    it[0] = yrrGameNextX(game, it[0]);
        //    it[1] = yrrGameNextY(game, it[1]);
        //}
    }
}

