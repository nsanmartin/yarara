#ifndef __H_YRR_MEDIA_H_
#define __H_YRR_MEDIA_H_

#include <stdbool.h>

#include <SDL.h>

#include <yrr-point.h>
#include <yrr-media.h>

typedef struct YrrGame YrrGame;

typedef enum { YrrK_a, YrrK_b, YrrK_r, YrrK_q, YrrK_Left, YrrK_Right, YrrK_Up, YrrK_Down } YrrKey;

typedef struct {
  YrrKey* data;
  size_t sz;
  YrrKey* front;
  YrrKey* back;
} YrrKeyQueue;

typedef struct YrrMedia {
    SDL_Window* window;
    int windowWidth, windowHeight;
    SDL_Renderer* renderer;
    SDL_Event event;

    YrrKeyQueue* keyQueue;
} YrrMedia;

YrrMedia* yrrNewMedia(YrrPoint winsz);
void yrrFreeMedia(YrrMedia* media);


// utils

YrrKeyQueue* yrrNewKeyQueue(size_t size) ;
void yrrFreeKeyQueue(YrrKeyQueue* q);
int yrrKeyQueuePushBack(YrrKeyQueue q[static 1], YrrKey k) ;
bool yrrKeyQueueIsEmpty(const YrrKeyQueue q[static 1]) ;
YrrKey yrrKeyQueuePopFront(YrrKeyQueue q[static 1]) ;

#endif
