#ifndef __H_YRR_VELOCITY_H_
#define __H_YRR_VELOCITY_H_

typedef enum { YrrNorth, YrrSouth, YrrEast, YrrWest } YrrDirection ;

typedef struct {
    int x, y;
} YrrVelocity;


YrrVelocity yrr_velocity_from_direction(YrrDirection dir) ;
#endif
