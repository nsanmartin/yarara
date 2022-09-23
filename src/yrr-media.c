#include <yrr-media.h>
#include <SDL2/SDL.h>

void yrr_media_init(YrrMedia* media) {
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        exit (1);
    }
    
    atexit (SDL_Quit);

    //Window
    media->window = SDL_CreateWindow(
        "HW",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        media->windowWidth,
        media->windowHeight,
        SDL_WINDOW_SHOWN
    );
    
    if (media->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        exit(1);
    }
    
    //Renderer
    media->renderer = SDL_CreateRenderer(
        media->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (media->renderer == NULL) {
        SDL_DestroyWindow(media->window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(1);
    }
}


void yrr_media_close(YrrMedia* media) { SDL_DestroyWindow(media->window); }

void yrrGameTitleScreenRender(YrrGame* g) {
}

void yrr_media_render(YrrMedia* media) {
    //SDL_RenderPresent(media->renderer);
}


void yrr_media_draw_block(YrrMedia* media) {

}
