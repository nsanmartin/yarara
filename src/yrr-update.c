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


    if (yrrYararaGetsHitByBlock(yr, next)) {
        game->quit = true;
        game->state = YrrGameOverState;
    }

    if (yrr_point_eq(next, food)) {
        ++game->points;
        yr->food = yr->back - yr->front;
        YrrPoint p = game->board->level.food;

        // if player won this won't stop
        do {
            p.x = ((p.x + 1) * 71) % game->board->width;
            p.y = ((p.y - 1) * 371) % game->board->height;
        } while(yrrYararaGetsHitByBlock(yr, p));

        game->board->level.food = p;
    }

    if (yr->food > 0) {
        --yr->food;

        yrrYararaPushBack(yr, next.x, next.y);
        

    } else {
        yrrYararaPopFront(yr);
        yrrYararaPushBack(yr, next.x, next.y);
    }
}

