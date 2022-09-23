#include <yrr-yarara.h>

YrrYarara yrrNewYarara(size_t n) {
    size_t size = 2 * sizeof(int);
    int* points = malloc(size);

    YrrYarara yr = {
        .points = points,
        .size = size,
        .back = points,
        .front = points,
        .vel = yrr_velocity_from_direction(YrrSouth)
    };

    return yr;
}

void yrrFreeYarara(YrrYarara* y) {
    free(y->points);
}

void yrrYararaPopFront(YrrYarara* yarara) {
    yarara->front += 2;
}


void yrrYararaPushBack(YrrYarara* yar, int x, int y) {
    if (yar->back >= yar->points + yar->size) {
        if (yar->front > yar->points) {
            size_t n = yar->back - yar->front;
            memcpy(yar->points, yar->front, n);
            yar->front = yar->points;
            yar->back = yar->points + n;
        } else {
            yar->points = realloc(yar->points, 2 * yar->size);
            yar->front = yar->points;
            yar->back = yar->points + yar->size;
            yar->size *= 2;
        }
    }

    yar->back[0] = x;
    yar->back[1] = y;
    yar->back += 2;
}

