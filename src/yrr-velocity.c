#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <yrr-velocity.h>

YrrVelocity yrr_velocity_from_direction(YrrDirection dir) {
    YrrVelocity rv = { .x = 0, .y = 0 };
    switch (dir) {
        case YrrNorth:
            rv.x = 0;
            rv.y = -1;
            break;

        case YrrSouth:
            rv.x = 0;
            rv.y = 1;
            break;

        case YrrEast:
            rv.x = -1;
            rv.y = 0;
            break;

        case YrrWest:
            rv.x = 1;
            rv.y = 0;
            break;

        default:
             fprintf(stderr, "Wrong direction, exiting\n");
             exit(1);
    }

    return rv;
}

YrrDirection yrr_direction_from_velocity(YrrVelocity v) {
    if (v.x == 0 && v.y == -1) { return YrrNorth; };
    if (v.x == 0 && v.y == 1) { return YrrSouth; };
    if (v.x == -1 && v.y == 0) { return YrrEast; };
    if (v.x == 1 && v.y == 0) { return YrrWest; };
    assert(false);
}

