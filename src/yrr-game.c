#include <yrr-mem.h>

#include <yrr-media.h>
#include <yrr-board.h>
#include <yrr-game.h>
#include <yrr-yarara.h>
#include <yrr-title.h>

void yrrGamePlayStateProcessInput(YrrGame game[static 1]) ;
void yrrGameTitleStateUpdate(YrrGame g[static 1]) ;
void yrrGameTitleStateProcessInput(YrrGame game[static 1]) ;
void yrrGamePlayStateUpdate(YrrGame* g) ;

void yrrGameTitleStateRender(YrrGame g[static 1]) ;
void yrrGamePlayStateRender(YrrGame g[static 1]) ;

void yrrFreeGame(YrrGame* game) {
    if (game) {
        yrrFreeMedia(game->media);
        yrrFreeBoard(game->board);
        free(game);
    }
}

YrrGame* yrrNewGame(YrrPoint win_sz, YrrPoint board_sz) {

    YrrMedia* media = yrrNewMedia(win_sz);
    if (!media) {
        return NULL;
    }

    YrrBoard* board = yrrNewBoard(board_sz);
    if (!board) {
        yrrFreeMedia(media);
        return NULL;
    }

    YrrTitle* title = yrrGetTitle();

    YrrGame* rv = malloc(sizeof(YrrGame));
    if (!rv) {
        yrrFreeMedia(media);
        yrrFreeBoard(board);
        return NULL;
    }

    *rv = (YrrGame) {
        .quit = false,
        .media = media,
        .state = YrrStateTitle,
        .board = board,
        .process_input = &yrrGameTitleStateProcessInput,
        .update = &yrrGameTitleStateUpdate,
        .render = &yrrGameTitleStateRender,
        .title = title,
        .points = 0
    };

    rv->board->offset = (YrrPoint){ .x = yrrGameGetBlockWidth(rv), .y = yrrGameGetBlockHeight(rv) };
    return rv;
}

int yrrResetGame(YrrGame game[static 1]) {
    if (game == NULL) { return -1; }
    int error = yrrResetBoard(game->board);
    if (error) { return error; }
    *game = (YrrGame) {
        .quit = false,
        .media = game->media,
        .state = YrrStateTitle,
        .board = game->board,
        .process_input = &yrrGameTitleStateProcessInput,
        .update = &yrrGameTitleStateUpdate,
        .render = &yrrGameTitleStateRender,
        .title = game->title,
        .points = 0
    };
    return 0;
}

void yrrChangeStateMethods(YrrGame game[static 1], YrrGameState new_state) {

    switch (new_state) {
        case YrrStatePlay:
            game->process_input = yrrGamePlayStateProcessInput;
            game->update = yrrGamePlayStateUpdate;
            game->render = yrrGamePlayStateRender;
            break;
        default:
            return;
            // todo...
    }
    game->state = new_state;
}

void yrrGamePrintResults(YrrGame g[static 1]) {
    if (!g || !g->board || !g->board->players || !g->board->players->beg) {
        fprintf(stderr, "error: invalid game.");
    } else {
        YrrPlayer* compu = g->board->players->beg;
        YrrPlayer* human = g->board->players->beg + 1;
        char* winner = compu->yarara->alive ? "compu" : "human";
        printf("Game over, %s won. Human score: %d, compu score: %d.\n",
                winner, human->score, compu->score);
    }
}

SDL_Rect yrr_block_to_sdl_rect(YrrGame game[static 1], int x, int y) {
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


SDL_Rect yrr_block_to_sdl_rect_mod_board(YrrGame g[static 1], int x, int y) {
    x %= g->board->width;
    y %= g->board->height;
    return yrr_block_to_sdl_rect(g, x, y);
}
