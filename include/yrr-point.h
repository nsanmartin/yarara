#ifndef __H_YRR_POINT_H_
#define __H_YRR_POINT_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int x, y;
} YrrPoint;

typedef struct {
    YrrPoint* beg;
    size_t capacity;
    YrrPoint* end;
} YrrVecPoints;

bool yrr_point_eq(YrrPoint p, YrrPoint q) ;

YrrVecPoints* yrrNewVecPoints(size_t cap);
int yrrVecPointsPushBack(YrrVecPoints* ps, YrrPoint p);
#endif
