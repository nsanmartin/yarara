#include <assert.h>

#include <yrr-media.h>
//#include <yrr-game.h>

YrrKeyQueue yrrNewKeyQueue(size_t size) {
    YrrKey* data = malloc(size * sizeof (YrrKey));
    YrrKeyQueue rv = { .data = data, .sz = size, .front = data, .back = data };
    return rv;
}

bool yrrKeyQueueIsEmpty(const YrrKeyQueue* q) { return q->front >= q->back; }

void yrrKeyQueuePushBack(YrrKeyQueue* q, YrrKey k) {
    if (q->back >= q->data + q->sz) {
        if (q->front > q->data) {
            size_t n = q->back - q->front;
            memmove(q->data, q->front, n * sizeof(YrrKey));
            q->front = q->data;
            q->back = q->data + n;
        } else {
            q->data = realloc(q->data, 2 * q->sz * sizeof(YrrKey));
            if (q->data == NULL) {
                fprintf(stderr, "Realloc error, aborting\n");
                exit(1);
            }
            q->front = q->data;
            q->back = q->data + q->sz;
            q->sz *= 2;
        }
    }
    q->back[0] = k;
    ++q->back;
}

YrrKey yrrKeyQueuePopFront(YrrKeyQueue* q) {
    assert(q->front < q->back);
    return *q->front++;
}
