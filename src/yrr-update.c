#include <yrr-game.h>
#include <yrr-media.h>

#include <stdio.h>
void yrrGameTitleStateUpdate(YrrGame* g) {
    ++g->title->offset.x;
    ++g->title->offset.y;
}

void yrrGamePlayStateReadInput(YrrGame* g) {
    YrrKeyQueue* q = g->media->keyQueue;
    YrrYarara* yr = g->board->yarara;
    while (!yrrKeyQueueIsEmpty(q)) {
        YrrKey k = yrrKeyQueuePopFront(q);
        switch (k) {
            case YrrK_Left:
                yr->next_vel = yrr_velocity_from_direction(YrrEast);
                break;
            case YrrK_Right:
                yr->next_vel = yrr_velocity_from_direction(YrrWest);
                break;
            case YrrK_Up:
                yr->next_vel = yrr_velocity_from_direction(YrrNorth);
                break;
            case YrrK_Down:
                yr->next_vel = yrr_velocity_from_direction(YrrSouth);
                break;
            default:
                // do nothing
                break;
        }
    }

    if (yr->vel.x + yr->next_vel.x != 0 || yr->vel.x + yr->next_vel.x != 0) {
        yr->vel = yr->next_vel;
    }
}

void yrrGamePlayStateUpdate(YrrGame* game) {

    yrrGamePlayStateReadInput(game) ;
    YrrYarara* yr = game->board->yarara;

    //YrrPoint next = yrrYararaPlayStateUpdateHumanPlayer(yr, game->board);
    YrrPoint next = yrrYararaPlayStateUpdateAutomatePlayer(yr, game->board);

    if (!yr->alive) {
        game->quit = true;
        game->state = YrrStateGameOver;
    }

    YrrPoint food = game->board->level.food;
    if (yrr_point_eq(next, food)) {
        ++game->points;
        yr->food = yr->back - yr->front;
        YrrPoint p = game->board->level.food;

        // if board is filled this won't stop, but is unlikely
        do {
            p.x =  ((p.x + 1) * 71) % game->board->width;
            p.y =  ((game->board->height + (p.y - 1)) * 371) % game->board->height;
        } while(yrrYararaGetsHitByBlock(yr, p));

        printf(" %d %d\n", p.x, p.y);
        game->board->level.food = p;
    }
}

