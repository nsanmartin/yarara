#include <yrr-game.h>
#include <yrr-media.h>
#include <yrr-title.h>
#include <yrr-yarara.h>

#include <stdio.h>
void yrrGameTitleStateUpdate(YrrGame g[static 1]) {
    ++g->title->offset.x;
    ++g->title->offset.y;
}

void yrrGamePlayStateReadInput(YrrGame g[static 1]) {
    YrrKeyQueue* q = g->media->keyQueue;
    //, the second is the human, use another aproach
    YrrYarara* yr = g->board->players->beg[1].yarara;
    if (!yrrKeyQueueIsEmpty(q)) {
        YrrKey k = yrrKeyQueuePopFront(q);
        switch (k) {
            case YrrK_Left:
                yr->next_vel = yrr_velocity_east();
                break;
            case YrrK_Right:
                yr->next_vel = yrr_velocity_west();
                break;
            case YrrK_Up:
                yr->next_vel = yrr_velocity_north();
                break;
            case YrrK_Down:
                yr->next_vel = yrr_velocity_south();
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

void yrrGamePlayStateUpdate(YrrGame game[static 1]) {

    yrrGamePlayStateReadInput(game) ;
    YrrPlayer* compu = game->board->players->beg;
    YrrPlayer* human = game->board->players->beg + 1;

    YrrResultPoint next_human = yrrYararaPlayStateUpdateHumanPlayer(human->yarara, game->board);
    if (next_human.error) {
        game->quit = true;
        return;
    }
    YrrResultPoint next_compu = yrrYararaPlayStateUpdateAutomatePlayer(compu->yarara, game->board);
    if (next_compu.error) {
        game->quit = true;
        return;
    }

    if (!compu->yarara->alive || !human->yarara->alive) {
        game->quit = true;
        game->state = YrrStateGameOver;
    } 

    YrrPoint food = game->board->level.food;
    bool food_eaten = false;
    if (yrr_point_eq(next_human.value, food)) {
        ++human->score;
        human->yarara->food = human->yarara->back - human->yarara->front;
        food_eaten = true;
    }

    if (yrr_point_eq(next_compu.value, food)) {
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

