#ifndef __H_YRR_MEDIA_H_
#define __H_YRR_MEDIA_H_

#include <stdbool.h>

#include <SDL2/SDL.h>

typedef struct YrrGame YrrGame;

typedef enum { YrrK_a, YrrK_b, YrrK_r, YrrK_q, YrrK_Left, YrrK_Right, YrrK_Up, YrrK_Down } YrrKey;

typedef struct {
  YrrKey* data;
  size_t sz;
  YrrKey* front;
  YrrKey* back;
} YrrKeyQueue;

typedef struct {
    SDL_Window* window;
    int windowWidth, windowHeight;
    SDL_Renderer* renderer;
    SDL_Event event;

    YrrKeyQueue keyQueue;
    //std::deque<Key> mKeyQueue;
    //World* world;
} YrrMedia;

void yrr_media_init(YrrMedia* media);
void yrr_media_close(YrrMedia* media) ;
//void yrr_media_render(YrrMedia* game) ;
//void yrr_media_render_game(YrrGame* game) ;
void yrr_media_render(YrrMedia* media) ;

void yrr_media_draw_block(YrrMedia* media);
void yrrGameTitleStateRender(YrrGame* g) ;
void yrrGamePlayStateRender(YrrGame* g) ;

// utils

YrrKeyQueue yrrNewKeyQueue(size_t size) ;
void yrrKeyQueuePushBack(YrrKeyQueue* q, YrrKey k) ;
bool yrrKeyQueueIsEmpty(const YrrKeyQueue* q) ;
YrrKey yrrKeyQueuePopFront(YrrKeyQueue* q) ;
#endif
