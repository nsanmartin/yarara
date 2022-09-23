#ifndef __H_YRR_MEDIA_H_
#define __H_YRR_MEDIA_H_

#include <SDL2/SDL.h>

typedef struct YrrGame YrrGame;

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
void yrr_media_close(YrrMedia* media) ;
//void yrr_media_render(YrrMedia* game) ;
//void yrr_media_render_game(YrrGame* game) ;
void yrr_media_render(YrrMedia* media) ;

void yrr_media_draw_block(YrrMedia* media);
void yrrGameRenderTitleScreen(YrrGame* g) ;
#endif
