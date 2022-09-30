#include <yrr-game.h>
#include <yrr-media.h>

#include <stdio.h>
void yrrGameTitleStateUpdate(YrrGame* g) {
    ++g->title->offset.x;
    ++g->title->offset.y;
}

void yrrGamePlayStateReadInput(YrrGame* g) {
    YrrKeyQueue* q = g->media->keyQueue;
    //, the second is the human, use another aproach
    YrrYarara* yr = g->board->players->beg[1].yarara;
    if (!yrrKeyQueueIsEmpty(q)) {
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
    YrrPlayer* compu = game->board->players->beg;
    YrrPlayer* human = game->board->players->beg + 1;

    YrrPoint next_human = yrrYararaPlayStateUpdateHumanPlayer(human->yarara, game->board);
    YrrPoint next_compu = yrrYararaPlayStateUpdateAutomatePlayer(compu->yarara, game->board);

    if (!compu->yarara->alive || !human->yarara->alive) {
        game->quit = true;
        game->state = YrrStateGameOver;
    } 

    YrrPoint food = game->board->level.food;
    bool food_eaten = false;
    if (yrr_point_eq(next_human, food)) {
        ++human->score;
        human->yarara->food = human->yarara->back - human->yarara->front;
        food_eaten = true;
    }

    if (yrr_point_eq(next_compu, food)) {
        ++compu->score;
        compu->yarara->food = compu->yarara->back - compu->yarara->front;
        food_eaten = true;
    }
    if (food_eaten) {
        YrrPoint p = game->board->level.food;

        // if board is filled this won't stop, but is unlikely
        do {
            p.x =  ((p.x + 1) * 41) % game->board->width;
            p.y =  ((game->board->height + (p.y - 1)) * 277) % game->board->height;
        } while(yrrBoardBlockOccupiedByAnyYarara(game->board, p));

        game->board->level.food = p;
    }
}

