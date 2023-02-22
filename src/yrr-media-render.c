#include <yrr-media.h>
#include <yrr-board.h>
#include <yrr-game.h>
#include <yrr-media-sdl.h>
#include <yrr-title.h>

void yrr_render_title(YrrGame* g) {
    for (size_t i = 0; i < g->title->size; ++i) {
        for (size_t j = 0; j < g->title->data[i].size; ++j) {
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
    SDL_Delay(173);
}


void yrr_render_players(YrrGame* g) {
    YrrVecPlayers* players = g->board->players;
    SDL_SetRenderDrawColor(g->media->renderer, 255, 148, 57, 253 );
    for(YrrPlayer* it = players->beg; it < players->end; ++it) {
        YrrYarara* yr = it->yarara;
        for (YrrPoint* it = yr->front; it < yr->back; ++it) {
            SDL_Rect r = yrr_block_to_sdl_rect_mod_board(g, it->x, it->y);
            SDL_RenderFillRect(g->media->renderer, &r );
        }
    }
}

void yrr_render_level(YrrGame* g) {
    YrrPoint p = g->board->level.food;
    SDL_Rect food = yrr_block_to_sdl_rect_mod_board(g, p.x, p.y);

    SDL_SetRenderDrawColor(g->media->renderer, 155, 181, 57, 253 );
    SDL_RenderFillRect(g->media->renderer, &food);
}

void yrr_render_frame(YrrGame* g) {
    SDL_SetRenderDrawColor(g->media->renderer, 55, 48, 57, 53 );

    int block_width = yrrGameGetBlockWidth(g);
    YrrPoint offset = g->board->offset;

    int block_height = yrrGameGetBlockHeight(g);
    // right |
    SDL_Rect frame = {
        .x = g->media->windowWidth - block_width,
        .y = -block_height + offset.y,
        .w = block_width,
        .h = g->media->windowHeight //+ block_height
    };
    SDL_RenderFillRect(g->media->renderer, &frame);
    
    // bottom ==
    frame = (SDL_Rect) {
        .x = offset.x,
        .y = g->media->windowHeight,
        .w = g->media->windowWidth - offset.x,
        .h = block_height
    };
    SDL_RenderFillRect(g->media->renderer, &frame);

    // top ==
    frame = (SDL_Rect) {
        .x = offset.x - block_width,
        .y = offset.y - block_height,
        .w = g->media->windowWidth,
        .h = block_height
    };
    SDL_RenderFillRect(g->media->renderer, &frame);

    // left |
    frame = (SDL_Rect) {
        .x = offset.x - block_width,
        .y = offset.y,
        .w = block_width,
        .h = g->media->windowHeight
    };
    SDL_RenderFillRect(g->media->renderer, &frame);
}


void yrrGamePlayStateRender(YrrGame* g) {
    SDL_SetRenderDrawColor(g->media->renderer, 0, 81, 177, 253 );
    SDL_RenderClear(g->media->renderer);

    yrr_render_players(g);
    yrr_render_level(g);

    yrr_render_frame(g);
    SDL_RenderPresent(g->media->renderer);
}
