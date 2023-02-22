#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <yrr-velocity.h>

YrrVelocity yrr_velocity_north(void) { return (YrrVelocity) { .x =  0, .y = -1 }; }
YrrVelocity yrr_velocity_south(void) { return (YrrVelocity) { .x =  0, .y =  1 }; }
YrrVelocity yrr_velocity_east(void)  { return (YrrVelocity) { .x = -1, .y =  0 }; }
YrrVelocity yrr_velocity_west(void)  { return (YrrVelocity) { .x =  1, .y =  0 }; }

