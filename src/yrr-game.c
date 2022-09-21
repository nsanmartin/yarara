#include <yrr-game.h>

void yrrTitleStateProcessInput(YrrGame* game) {
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ) {

            case SDLK_s:
                //mWorld.changeState(World::StateEnum::Move);
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



void yrr_process_input(YrrGame* game) {
     yrrTitleStateProcessInput(game);   
}

void yrr_update(YrrGame* game) {
    //todo
}


void yrr_render(YrrGame* game) {

    SDL_SetRenderDrawColor(game->media->renderer, 255, 0, 0, 255 );
    //SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderClear(game->media->renderer);
    SDL_RenderPresent(game->media->renderer);
}
