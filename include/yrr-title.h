#ifndef __H_YRR_TITLE_H_
#define __H_YRR_TITLE_H_

#include <yrr-board.h>
#include <yrr-util.h>

typedef struct {
    YrrPoint* data;
    size_t size;
} YrrLetter;

typedef struct {
    YrrLetter* data;
    size_t size;
} YrrTitle;

#define yrrArrayFromArray(ARR) { .data = ARR, .size = LEN(ARR) }

YrrTitle* yrrGetTitle() ;

#endif
