#include <yrr-media.h>
#include <SDL2/SDL.h>

#include <yrr-point.h>


int yrr_media_init(YrrMedia* media) {
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return -1;
    }

    atexit (SDL_Quit);

    media->window = SDL_CreateWindow(
        "yarara",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        media->windowWidth,
        media->windowHeight,
        SDL_WINDOW_SHOWN
    );
    
    if (media->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        return -1;
    }
    
    media->renderer = SDL_CreateRenderer(
        media->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (media->renderer == NULL) {
        SDL_DestroyWindow(media->window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

void yrrFreeMedia(YrrMedia* media) {
    SDL_DestroyWindow(media->window); 
    yrrFreeKeyQueue(media->keyQueue);
    free(media);
}

YrrMedia* yrrNewMedia(YrrPoint winsz) {
    YrrKeyQueue* key_queue = yrrNewKeyQueue(300);
    if (!key_queue) {
        return NULL;
    }

    YrrMedia* rv = malloc(sizeof(YrrMedia));
    if (!rv) {
        return NULL;
    }

    *rv = (YrrMedia) {
        .window = NULL,
        .windowWidth = winsz.x,
        .windowHeight = winsz.y, 
        .keyQueue = key_queue,
        .renderer = NULL
    };

    if(yrr_media_init(rv) != 0) {
        free(rv);
        return NULL;
    }
    return rv;
}



void yrrGameTitleScreenRender(YrrGame* g) {
}

void yrr_media_render(YrrMedia* media) {
    //SDL_RenderPresent(media->renderer);
}


void yrr_media_draw_block(YrrMedia* media) {

}
