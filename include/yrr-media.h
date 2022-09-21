#ifndef __H_YRR_MEDIA_H_
#define __H_YRR_MEDIA_H_
#include <SDL2/SDL.h>


enum Key { a, b, r, q, Left, Right, Up, Down };

typedef struct {
    SDL_Window* window;
    int windowWidth, windowHeight;
    SDL_Renderer* renderer;
    SDL_Event event;

    //std::deque<Key> mKeyQueue;
    //World* world;
} YrrMedia;

void yrr_media_init(YrrMedia* media);

#endif
