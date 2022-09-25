#include <assert.h>
#include <yrr-yarara.h>
#include <stdio.h>

//TODO: use array of data
YrrYarara yrrNewYarara(size_t size) {
    size_t nbytes = size * sizeof(YrrPoint);
    YrrPoint* data = malloc(nbytes);

    YrrYarara yr = {
        .data = data,
        .size   = size,
        .back   = data,
        .front  = data,
        .vel    = yrr_velocity_from_direction(YrrWest),
        .food   = 0
    };

    return yr;
}

void yrrFreeYarara(YrrYarara* y) {
    free(y->data);
}

void yrrYararaPopFront(YrrYarara* yarara) {
    assert(yarara->front < yarara->back);
    ++yarara->front;
}


void yrrYararaPushBack(YrrYarara* yar, int x, int y) {
    //printf("yarara push back\n");
    if (yar->back >= yar->data + yar->size) {
        //fprintf(stderr, "back <= ps + sz\n");
        //exit(1);
        if (yar->front > yar->data) {
            printf("move head\n");

            size_t npoints = yar->back - yar->front;
            assert(yar->front + npoints < yar->data + yar->size);
            memcpy(yar->data, yar->front, npoints * sizeof(YrrPoint));
            //for(int i = 0; i < npoints; ++i) {
            //    yar->data[i] = yar->front[i];
            //}
            yar->front = yar->data;
            yar->back = yar->data + npoints;
        } else {
        printf("realloc head\n");
            yar->data = realloc(yar->data, 2 * yar->size);
            if (yar->data == NULL) {
                fprintf(stderr, "Realloc error, aborting\n");
                exit(1);
            }
            yar->front = yar->data;
            yar->back = yar->data + yar->size;
            yar->size *= 2;
        }
    }

    yar->back[0].x = x;
    yar->back[0].y = y;
    ++yar->back;
    //yar->back = yar->back + 2;
}

YrrPoint yrrYararaGetBackToPoint(YrrYarara* yr) {
    assert(yr->back > yr->front);
    return yr->back[-1];
}

