#include <assert.h>

#include <yrr-media.h>
#include <yrr-point.h>

void yrrFreeKeyQueue(YrrKeyQueue* queue) {
    if (queue) {
        free(queue->data);
        free(queue);
    }
}

YrrKeyQueue* yrrNewKeyQueue(size_t size) {

    YrrKey* data = malloc(size * sizeof (YrrKey));
    if (!data) {
        return NULL;
    }
    YrrKeyQueue* queue = malloc(sizeof(YrrKeyQueue));
    if (!queue) {
        free(data);
        return NULL;
    }

    *queue = (YrrKeyQueue) { .data = data, .sz = size, .front = data, .back = data };
    return queue;
}

void yrrKeyQueueFree(YrrKeyQueue* q) {
    free(q->data);
    free(q);

}

bool yrrKeyQueueIsEmpty(const YrrKeyQueue q[static 1]) { return q->front >= q->back; }

int yrrKeyQueuePushBack(YrrKeyQueue q[static 1], YrrKey k) {
    if (q->back >= q->data + q->sz) {
        if (q->front > q->data) {
            size_t n = q->back - q->front;
            memmove(q->data, q->front, n * sizeof(YrrKey));
            q->front = q->data;
            q->back = q->data + n;
        } else {
            q->data = realloc(q->data, 2 * q->sz * sizeof(YrrKey));
            if (q->data == NULL) {
                fprintf(stderr, "Realloc error\n");
                return -1;
            }
            q->front = q->data;
            q->back = q->data + q->sz;
            q->sz *= 2;
        }
    }
    q->back[0] = k;
    ++q->back;
    return 0;
}

YrrKey yrrKeyQueuePopFront(YrrKeyQueue q[static 1]) {
    assert(q->front < q->back);
    return *q->front++;
}
