#include <yrr-media.h>
#include <yrr-board.h>
#include <yrr-game.h>
#include <yrr-media-sdl.h>

void yrr_render_title(YrrGame* g) {
    for (int i = 0; i < g->title->size; ++i) {
        for (int j = 0; j < g->title->data[i].size; ++j) {
            YrrPoint p = g->title->data[i].data[j];
            p.x += 3*i + g->title->offset.x;
            p.y += g->title->offset.y;
            SDL_Rect r = yrr_block_to_sdl_rect_mod_board(g, p.x, p.y);
            SDL_RenderFillRect(g->media->renderer, &r );

        }
    }
}

void yrrGameTitleStateRender(YrrGame* g) {
    SDL_SetRenderDrawColor(g->media->renderer, 0, 81, 177, 253 );
    SDL_RenderClear(g->media->renderer);
    SDL_SetRenderDrawColor(g->media->renderer, 155, 181, 57, 253 );

    yrr_render_title(g);

    SDL_RenderPresent(g->media->renderer);
}


YrrPoint yrrPointFromArrayPoint(int* arr) {
    YrrPoint p;
    p.x = arr[0];
    p.y = arr[1];
    return p;
}

void yrr_render_yarara(YrrGame* g) {
    SDL_SetRenderDrawColor(g->media->renderer, 255, 148, 57, 253 );
    YrrYarara yr = g->board->yarara;
    for (YrrPoint* it = yr.front; it < yr.back; ++it) {
        SDL_Rect r = yrr_block_to_sdl_rect_mod_board(g, it->x, it->y);
        SDL_RenderFillRect(g->media->renderer, &r );
    }
}

void yrr_render_level(YrrGame* g) {
    YrrPoint p = g->board->level.food;
    SDL_Rect food = yrr_block_to_sdl_rect_mod_board(g, p.x, p.y);

    SDL_SetRenderDrawColor(g->media->renderer, 155, 181, 57, 253 );
    SDL_RenderFillRect(g->media->renderer, &food);
}

void yrrGamePlayStateRender(YrrGame* g) {
    SDL_SetRenderDrawColor(g->media->renderer, 0, 81, 177, 253 );
    SDL_RenderClear(g->media->renderer);


    yrr_render_yarara(g);
    yrr_render_level(g);

    SDL_RenderPresent(g->media->renderer);
}
