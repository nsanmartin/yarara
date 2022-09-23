#include <stdio.h>

#include <yrr-game.h>
#include <yrr-media.h>

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

//void yrrTitleStateUpdate(YrrGame* game) {
void yrrPlayStateUpdate(YrrGame* game) {
    //todo

    YrrYarara yr = game->board->yarara;
    YrrVelocity v = yr.vel;
    if (yr.back > yr.points) {
        yr.back[-2] = (yr.back[-2] + v.x) % game->board->width;
        yr.back[-1] = (yr.back[-1] + v.y) % game->board->height;
    }
}

void yrrGameTitleStateUpdate(YrrGame* g) {
}

void yrr_update(YrrGame* game) {
    //todo

    YrrYarara yr = game->board->yarara;
    YrrVelocity v = yr.vel;
    if (yr.back > yr.points) {
        yr.back[-2] = (yr.back[-2] + v.x) % game->board->width;
        yr.back[-1] = (yr.back[-1] + v.y) % game->board->height;
    }

}



SDL_Rect yrr_block_to_sdl_rect(YrrGame* game, int x, int y) {
    int block_width = game->media->windowWidth / game->board->width; 
    int block_height = game->media->windowHeight / game->board->height; 
    
    SDL_Rect rv = {
        .x = x * block_width, 
        .y = y * block_height,
        .w = block_width,
        .h = block_height
    };
    return rv;
}


void yrr_game_render_yarara(YrrGame* game) {
    YrrYarara yr = game->board->yarara;
    for (int* it = yr.front; it < yr.back; it += 2) {
        int x = it[0];
        int y = it[1];
        SDL_Rect r = yrr_block_to_sdl_rect(game, x, y);
        SDL_RenderFillRect(game->media->renderer, &r );
    }

    int title_offset = 7;
    for (int i = 0; i < game->title->size; ++i) {
        for (int j = 0; j < game->title->data[i].size; ++j) {
            YrrPoint p = game->title->data[i].data[j];
            p.x += 3*i + title_offset;
            p.y += title_offset;
            SDL_Rect r = yrr_block_to_sdl_rect(game, p.x, p.y);
            SDL_RenderFillRect(game->media->renderer, &r );

        }
    }
}

void yrr_game_render(YrrGame* game) {
    SDL_SetRenderDrawColor(game->media->renderer, 0, 81, 177, 253 );
    SDL_RenderClear(game->media->renderer);
    SDL_SetRenderDrawColor(game->media->renderer, 155, 181, 57, 253 );

    yrr_game_render_yarara(game);

    SDL_RenderPresent(game->media->renderer);
}
