//#include <stdlib.h>
#include <yrr-mem.h>
#include <yrr-point.h>

bool yrr_point_eq(YrrPoint p, YrrPoint q) {
    return p.x == q.x && p.y == q.y;
}

YrrVecPoints* yrrNewVecPoints(size_t capacity) {
    YrrPoint* data = malloc(capacity * sizeof(YrrPoint));
    if (!data) {
        return NULL;
    }
    YrrVecPoints* rv = malloc(sizeof(YrrVecPoints));
    if (!rv) {
        free(data);
        return NULL;
    }
    *rv = (YrrVecPoints) {
        .beg = data,
        .capacity = capacity,
        .end = data
    };

    return rv;
}

int yrrVecPointsPushBack(YrrVecPoints ps[static 1], YrrPoint p) { 
    if (ps->end >= ps->capacity + ps->beg) { 
        return -1;
    }
    *ps->end = p; 
    ++ps->end; 
    return 1;
}

