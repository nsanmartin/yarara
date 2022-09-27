#include <assert.h>
#include <yrr-yarara.h>
#include <stdio.h>

YrrYarara yrrNewYarara(size_t size) {
    size_t nbytes = size * sizeof(YrrPoint);
    YrrPoint* data = malloc(nbytes);

    YrrYarara yr = {
        .data   = data,
        .size   = size,
        .back   = data,
        .front  = data,
        .vel    = yrr_velocity_from_direction(YrrWest),
        .food   = 0
    };

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

void yrrYararaPushBack(YrrYarara* yr, int x, int y) {
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
