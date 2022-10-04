#include <assert.h>
#include <yrr-yarara.h>
#include <stdio.h>
#include <yrr-board.h>
#include <yrr-game.h>


YrrPoint yrrYararaNextPoint(YrrYarara* yr, int maxx, int maxy) {
    assert(yr->back >= yr->front);
    YrrPoint p = yr->back[-1];
    return (YrrPoint) {
        .x = (maxx + p.x + yr->vel.x) % maxx,
        .y = (maxy + p.y + yr->vel.y) % maxy
    };
}


YrrYarara* yrrNewYarara(size_t size, YrrPoint first) {
    size_t nbytes = size * sizeof(YrrPoint);
    YrrPoint* data = malloc(nbytes);
    if (!data) {
        return NULL;
    }

    YrrYarara* rv = malloc(sizeof(YrrYarara));
    if (!rv) {
        return NULL;
    }

    *rv = (YrrYarara) {
        .data   = data,
        .size   = size,
        .back   = data,
        .front  = data,
        .vel    = yrr_velocity_west(),
        .next_vel    = yrr_velocity_west(),
        .food   = 0,
        .alive = true
    };

    int error = yrrYararaPushBack(rv, first);
    if (error) {
        yrrFreeYarara(rv);
        return NULL;
    }

    return rv;
}

int yrrResetYarara(YrrYarara* yarara, YrrPoint first) {
    yarara->back = yarara->front = yarara->data;
    yarara->vel    = yrr_velocity_west();
    yarara->next_vel    = yrr_velocity_west();
    yarara->food   = 0;
    yarara->alive = true;
    int error = yrrYararaPushBack(yarara, first);
    return error;

}

void yrrFreeYarara(YrrYarara* y) {
    free(y->data);
    free(y);
}


void yrrYararaPopFront(YrrYarara* yarara) {
    assert(yarara->front < yarara->back);
    ++yarara->front;
}


bool no_more_place_at_end(YrrYarara* yr) {
    return yr->back >= yr->data + yr->size;
}

bool has_place_at_beg(YrrYarara* yr) {
    return yr->front > yr->data;
}

int yarara_push_back(YrrYarara* yr, int x, int y) {
    assert(yr->back <= yr->data + yr->size);
    if (no_more_place_at_end(yr)) {
        if (has_place_at_beg(yr)) {
            size_t npoints = yr->back - yr->front;
            memmove(yr->data, yr->front, sizeof(YrrPoint) * npoints);
            yr->front = yr->data;
            yr->back = yr->data + npoints;
        } else {
            size_t new_size = yr->size << 1;
            YrrPoint* new_data = realloc(yr->data, new_size * sizeof(YrrPoint));
            if (new_data == NULL) {
                fprintf(stderr, "Realloc error, aborting\n");
                return -1;
            }
            yr->data = new_data;
            yr->front = yr->data;
            yr->back = yr->data + yr->size;
            yr->size = new_size;
        }
    }

    assert(yr->back < yr->data + yr->size);
    yr->back[0].x = x;
    yr->back[0].y = y;
    ++yr->back;
    return 0;
}

int yrrYararaPushBack(YrrYarara* yr, YrrPoint p) {
    return yarara_push_back(yr, p.x, p.y);
}


YrrPoint yrrYararaGetBackToPoint(YrrYarara* yr) {
    assert(yr->back > yr->front);
    return yr->back[-1];
}

bool yrrYararaGetsHitByBlock(YrrYarara* yr, YrrPoint p) {
    for (YrrPoint* it = yr->front; it < yr->back; ++it) {
        if (yrr_point_eq(*it, p)) {
            return true;
        }
    }
    return false;
}

YrrVelocity rotate_90deg(YrrVelocity v) {
    return (YrrVelocity) { .x = v.y, .y = -v.x };
}

bool yrrBoardBlockOccupiedByAnyYarara(const YrrBoard* board, YrrPoint p) {
    YrrVecPlayers* ps = board->players;
    for (YrrPlayer* it = ps->beg; it < ps->end; ++it) {
        if (yrrYararaGetsHitByBlock(it->yarara, p)) {
            return true;
        }
    }
    return false;
}


void yrrYararaSetCompuNextVelocity(YrrYarara* yr, const YrrBoard* b) {
    const YrrPoint food = b->level.food;
    assert(yr->back > yr->front);
    YrrPoint p = yr->back[-1];
    yr->vel = (YrrVelocity){
        .x = p.x == food.x ? 0 : (food.x < p.x ? -1 : 1),
        .y = p.x != food.x ? 0 : (food.y < p.y ? -1 : 1)
    };

    for (int i = 0; yrrBoardBlockOccupiedByAnyYarara(b, yrrYararaNextPoint(yr, b->width, b->height)) && i < 4; ++i) {
        yr->vel = rotate_90deg(yr->vel);
    }
}


int yarara_move_next(YrrYarara* yr, YrrPoint next, const YrrBoard* board) {
    if (yrrBoardBlockOccupiedByAnyYarara(board, next)) {
        yr->alive = false;
    }

    if (yr->food > 0) {
        --yr->food;

        int error = yrrYararaPushBack(yr, next);
        if (error) {
            return error;
        }
        

    } else {
        yrrYararaPopFront(yr);
        int error = yrrYararaPushBack(yr, next);
        if (error) {
            return -1;
        }

    }
    return 0;
}

YrrPoint yrrYararaPlayStateUpdateHumanPlayer(YrrYarara* yr, const YrrBoard* b) {

    const YrrPoint next = yrrYararaNextPoint(yr, b->width, b->height);

    yarara_move_next(yr, next, b);

    return next;
}


YrrPoint yrrYararaPlayStateUpdateAutomatePlayer(YrrYarara* yr, const YrrBoard* b) {

    yrrYararaSetCompuNextVelocity(yr, b);
    const YrrPoint next = yrrYararaNextPoint(yr, b->width, b->height);

    yarara_move_next(yr, next, b);

    return next;
}
