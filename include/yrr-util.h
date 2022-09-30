#ifndef __H_YRR_UTIL_H_
#define __H_YRR_UTIL_H_

#include <time.h>
#include <assert.h>
#include <yrr-point.h>

enum { NS_PER_SECOND = 1000000000, MS_PER_SECOND = 1000, NS_PER_MS = 1000000 };

#define LEN(ARR) (sizeof(ARR)/sizeof(ARR[0]))

#define yrrVecPushBack(VECP, ELEM) { \
        assert(VECP->end - VECP->beg < VECP->capacity); \
        *VECP->end = ELEM; \
        ++VECP->end; \
    };

#define yrrFreeVec(VECP) { \
    free(VECP->beg); \
    free(VECP); \
}

long get_time_millis();
YrrPoint get_pseudo_rand(YrrPoint minxs, YrrPoint maxys);
#endif

