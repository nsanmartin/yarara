#include <assert.h>
#include <yrr-yarara.h>
#include <stdio.h>
#include <yrr-board.h>

YrrYarara yrrNewYarara(size_t size) {
    size_t nbytes = size * sizeof(YrrPoint);
    YrrPoint* data = malloc(nbytes);

    YrrYarara yr = {
        .data   = data,
        .size   = size,
        .back   = data,
        .front  = data,
        .vel    = yrr_velocity_from_direction(YrrWest),
        .next_vel    = yrr_velocity_from_direction(YrrWest),
        .food   = 0,
        .alive = true
    };

    yrrYararaPushBack(&yr, (YrrPoint) { .x = 0, .y = 0});
    yrrYararaPushBack(&yr, (YrrPoint) { .x = 0, .y = 1});

    return yr;
}

void yrrFreeYarara(YrrYarara* y) {
    free(y->data);
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

void yarara_push_back(YrrYarara* yr, int x, int y) {
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
                exit(1);
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
}

void yrrYararaPushBack(YrrYarara* yr, YrrPoint p) {
    yarara_push_back(yr, p.x, p.y);
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

YrrPoint yrrYararaNextPoint(YrrYarara* yr, int maxx, int maxy) {
    assert(yr->back > yr->front);
    YrrPoint p = yr->back[-1];
    return (YrrPoint) {
        .x = (maxx + p.x + yr->vel.x) % maxx,
        .y = (maxy + p.y + yr->vel.y) % maxy
    };
}

YrrPoint yrrYararaPlayStateUpdateHumanPlayer(YrrYarara* yr, const YrrBoard* b) {

    const YrrPoint next = yrrYararaNextPoint(yr, b->width, b->height);
    if (yrrYararaGetsHitByBlock(yr, next)) {
        yr->alive = false;
    }

    if (yr->food > 0) {
        --yr->food;

        yrrYararaPushBack(yr, next);
        

    } else {
        yrrYararaPopFront(yr);
        yrrYararaPushBack(yr, next);
    }

    return next;
}

YrrPoint yrrYararaPlayStateUpdateAutomatePlayer(YrrYarara* yr, const YrrBoard* b) {

    const YrrPoint next = yrrYararaNextPoint(yr, b->width, b->height);
    if (yrrYararaGetsHitByBlock(yr, next)) {
        yr->alive = false;
    }

    if (yr->food > 0) {
        --yr->food;

        yrrYararaPushBack(yr, next);
        

    } else {
        yrrYararaPopFront(yr);
        yrrYararaPushBack(yr, next);
    }

    return next;
}
