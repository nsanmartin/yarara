#include <yrr-util.h>
#include <assert.h>

long get_time_millis() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec * MS_PER_SECOND + t.tv_nsec / NS_PER_MS;
}

YrrPoint get_pseudo_rand(YrrPoint mins, YrrPoint maxs) {
    assert(maxs.x > mins.x);
    assert(maxs.y > mins.y);

    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    int x = (maxs.x-mins.x) * ((double)(t.tv_nsec % 10))/10;
    int y = (maxs.y-mins.y) * ((double)((t.tv_nsec/10) % 10))/10;
    return (YrrPoint) { .x = mins.x + x, .y = mins.y + y };

}
