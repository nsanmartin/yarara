#include <yrr-media.h>
#include <yrr-point.h>
#include <yrr-game.h>

#include <SDL.h>

int yrr_media_init(YrrMedia media[static 1]) {
    
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
    
    int error = SDL_SetWindowFullscreen(media->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (error) {
        SDL_DestroyWindow(media->window);
        return error;
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
    if (media) {
        SDL_DestroyRenderer(media->renderer);
        SDL_DestroyWindow(media->window); 
        yrrFreeKeyQueue(media->keyQueue);
        free(media);
    }
}

YrrMedia* yrrNewMedia(YrrPoint winsz) {
    YrrKeyQueue* key_queue = yrrNewKeyQueue(300);
    if (!key_queue) {
        return NULL;
    }

    YrrMedia* rv = malloc(sizeof(YrrMedia));
    if (!rv) {
        yrrFreeKeyQueue(key_queue);
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
        yrrFreeKeyQueue(key_queue);
        free(rv);
        return NULL;
    }
    return rv;
}

