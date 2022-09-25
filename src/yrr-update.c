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
                if (yrr_direction_from_velocity(yr->vel) != YrrWest) {
                    yr->vel.x = -1;
                    yr->vel.y = 0;
                }
                break;
            case YrrK_Right:
                if (yrr_direction_from_velocity(yr->vel) != YrrEast) {
                    yr->vel.x = 1;
                    yr->vel.y = 0;
                }
                break;
            case YrrK_Up:
                if (yrr_direction_from_velocity(yr->vel) != YrrSouth) {
                    yr->vel.x = 0;
                    yr->vel.y = -1;
                }
                break;
            case YrrK_Down:
                if (yrr_direction_from_velocity(yr->vel) != YrrNorth) {
                    yr->vel.x = 0;
                    yr->vel.y = 1;
                }
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
        yr->food = yr->back - yr->front;
        YrrPoint p = game->board->level.food;
        p.x = ((p.x + 1) * 71) % game->board->width;
        p.y = ((p.y - 1) * 371) % game->board->height;
        game->board->level.food = p;
    }

    if (yr->food > 0) {
        --yr->food;

        yrrYararaPushBack(yr, next.x, next.y);
        

    } else {
        yrrYararaPushBack(yr, next.x, next.y);
        yrrYararaPopFront(yr);
    }
}

