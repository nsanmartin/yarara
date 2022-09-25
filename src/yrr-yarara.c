#include <assert.h>
#include <yrr-yarara.h>
#include <stdio.h>

YrrYarara yrrNewYarara(size_t n) {
    size_t size = n * 2 * sizeof(int);
    int* points = malloc(size);

    YrrYarara yr = {
        .points = points,
        .size   = size,
        .back   = points,
        .front  = points,
        .vel    = yrr_velocity_from_direction(YrrWest),
        .food   = 0
    };

    return yr;
}

void yrrFreeYarara(YrrYarara* y) {
    free(y->points);
}

void yrrYararaPopFront(YrrYarara* yarara) {
    assert(yarara->front < yarara->back);
    yarara->front += 2;
}


void yrrYararaPushBack(YrrYarara* yar, int x, int y) {
    if (yar->back >= yar->points + yar->size) {
        if (yar->front > yar->points) {
        printf("move head\n");
            size_t n = yar->back - yar->front;
            memcpy(yar->points, yar->front, n);
            yar->front = yar->points;
            yar->back = yar->points + n;
        } else {
        printf("realloc head\n");
            yar->points = realloc(yar->points, 2 * yar->size);
            if (yar->points == NULL) {
                fprintf(stderr, "Realloc error, aborting\n");
                exit(1);
            }
            yar->front = yar->points;
            yar->back = yar->points + yar->size;
            yar->size *= 2;
        }
    }

    yar->back[0] = x;
    yar->back[1] = y;
    yar->back += 2;
    //yar->back = yar->back + 2;
}

YrrPoint yrrYararaGetBackToPoint(YrrYarara* yr) {
    assert(yr->back > yr->front);

    YrrPoint rv = {
        .x = yr->back[-2],
        .y = yr->back[-1]
    };
    return rv;
}

