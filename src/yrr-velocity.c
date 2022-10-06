#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <yrr-velocity.h>

YrrVelocity yrr_velocity_north() { return (YrrVelocity) { .x =  0, .y = -1 }; }
YrrVelocity yrr_velocity_south() { return (YrrVelocity) { .x =  0, .y =  1 }; }
YrrVelocity yrr_velocity_east()  { return (YrrVelocity) { .x = -1, .y =  0 }; }
YrrVelocity yrr_velocity_west()  { return (YrrVelocity) { .x =  1, .y =  0 }; }

