#ifndef __H_YRR_VELOCITY_H_
#define __H_YRR_VELOCITY_H_

typedef enum { YrrNorth, YrrSouth, YrrEast, YrrWest } YrrDirection ;

typedef struct {
    int x, y;
} YrrVelocity;


YrrVelocity yrr_velocity_north(void); 
YrrVelocity yrr_velocity_south(void); 
YrrVelocity yrr_velocity_east(void);
YrrVelocity yrr_velocity_west(void); 

#endif
