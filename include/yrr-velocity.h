#ifndef __H_YRR_VELOCITY_H_
#define __H_YRR_VELOCITY_H_

typedef enum { YrrNorth, YrrSouth, YrrEast, YrrWest } YrrDirection ;

typedef struct {
    int x, y;
} YrrVelocity;


YrrVelocity yrr_velocity_north(); 
YrrVelocity yrr_velocity_south(); 
YrrVelocity yrr_velocity_east();
YrrVelocity yrr_velocity_west(); 

#endif
