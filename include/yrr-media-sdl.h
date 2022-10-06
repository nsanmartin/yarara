#ifndef __H_YRR_MEDIA_SDL_H_
#define __H_YRR_MEDIA_SDL_H_

#include <SDL.h>

#include <yrr-game.h>

SDL_Rect yrr_block_to_sdl_rect(YrrGame* game, int x, int y) ;
SDL_Rect yrr_block_to_sdl_rect_mod_board(YrrGame* game, int x, int y);

#endif

