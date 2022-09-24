#ifndef __H_YRR_POINT_H_
#define __H_YRR_POINT_H_

#include <stdbool.h>

typedef struct {
    int x, y;
} YrrPoint;

bool yrr_point_eq(YrrPoint p, YrrPoint q) ;

#endif
