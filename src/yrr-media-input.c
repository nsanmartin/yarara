#include <yrr-game.h>
#include <yrr-media.h>


void yrrGameTitleStateProcessInput(YrrGame* game) {
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ) {

            case SDLK_s:
                yrrChangeStateMethods(game, YrrStatePlay);
                break;

            case SDLK_q:
                game->quit = true;
                break;

            default:
                break;
            }
            break;
        case SDL_KEYUP:
            break;

        case SDL_QUIT:
            game->quit = true;
            break;

        default:
            break;
        }

    }
}

void yrrGamePlayStateProcessInput(YrrGame* g) {
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ) {

             case SDLK_LEFT:
                 yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Left);
                 break;
             case SDLK_RIGHT:
                 yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Right);
                 break;
             case SDLK_UP:
                 yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Up);
                 break;
            case SDLK_DOWN:
                 yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Down);
                break;

            case SDLK_q:
                g->quit = true;
                break;

            default:
                break;
            }
            break;
        case SDL_KEYUP:
            break;

        case SDL_QUIT:
            g->quit = true;
            break;

        default:
            break;
        }

    }
}
