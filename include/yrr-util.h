#ifndef __H_YRR_UTIL_H_
#define __H_YRR_UTIL_H_

#include <time.h>
#include <yrr-point.h>

enum { NS_PER_SECOND = 1000000000, MS_PER_SECOND = 1000, NS_PER_MS = 1000000 };

#define LEN(ARR) (sizeof(ARR)/sizeof(ARR[0]))

long get_time_millis();
YrrPoint get_pseudo_rand(YrrPoint minxs, YrrPoint maxys);
#endif

