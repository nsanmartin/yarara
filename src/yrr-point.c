#include <stdlib.h>
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
        return NULL;
    }
    *rv = (YrrVecPoints) {
        .beg = data,
        .capacity = capacity,
        .end = data
    };

    return rv;
}
