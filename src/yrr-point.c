#include <yrr-point.h>

bool yrr_point_eq(YrrPoint p, YrrPoint q) {
    return p.x == q.x && p.y == q.y;
}
