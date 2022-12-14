#include <yrr-game.h>
#include <yrr-media.h>

void yrrChangeStateMethods(YrrGame* game, YrrGameState new_state);

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
    int error = 0; 
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ) {

             case SDLK_LEFT:
                 error = yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Left);
                 if (error) {
                     g->quit = true;;
                     return;
                 }
                 break;
             case SDLK_RIGHT:
                 error = yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Right);
                 if (error) {
                     g->quit = true;;
                     return;
                 }
                 break;
             case SDLK_UP:
                 error = yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Up);
                 if (error) {
                     g->quit = true;;
                     return;
                 }
                 break;
            case SDLK_DOWN:
                 error = yrrKeyQueuePushBack(g->media->keyQueue, YrrK_Down);
                 if (error) {
                     g->quit = true;;
                     return;
                 }
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
