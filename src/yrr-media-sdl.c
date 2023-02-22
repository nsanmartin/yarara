#include <yrr-media.h>
#include <yrr-media-sdl.h>
#include <yrr-board.h>


SDL_Rect yrr_block_to_sdl_rect(YrrGame* game, int x, int y) {
    int block_width = (game->media->windowWidth - game->board->offset.x) / game->board->width; 
    int block_height = (game->media->windowHeight - game->board->offset.y) / game->board->height; 
    
    SDL_Rect rv = {
        .x = x * block_width, 
        .y = y * block_height,
        .w = block_width,
        .h = block_height
    };
    yrrBoardApplyOffset(game->board, &rv);
    return rv;
}


SDL_Rect yrr_block_to_sdl_rect_mod_board(YrrGame* g, int x, int y) {
    x %= g->board->width;
    y %= g->board->height;
    return yrr_block_to_sdl_rect(g, x, y);
}
