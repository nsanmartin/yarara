#ifndef __H_YRR_UTIL_H_
#define __H_YRR_UTIL_H_

#include <stdio.h>
#include <time.h>
#include <yrr-point.h>
#include <yrr-test.h>
#include <yrr-mem.h>

enum { NS_PER_SECOND = 1000000000, MS_PER_SECOND = 1000, NS_PER_MS = 1000000 };

typedef struct {
    int error, value;
} YrrResultInt;

typedef struct {
    int error;
    YrrPoint value;
} YrrResultPoint;

#define LEN(ARR) (sizeof(ARR)/sizeof(ARR[0]))


#define yrrFreeVec(VECP) { \
    free(VECP->beg); \
    free(VECP); \
}

long get_time_millis(void);
YrrPoint get_pseudo_rand(YrrPoint minxs, YrrPoint maxys);
#endif

