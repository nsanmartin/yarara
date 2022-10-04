#include <yrr-media.h>
#include <yrr-board.h>
#include <yrr-game.h>
#include <yrr-title.h>

void yrrGamePlayStateProcessInput(YrrGame* game) ;
void yrrGameTitleStateUpdate(YrrGame* g) ;
void yrrGameTitleStateProcessInput(YrrGame* game) ;
void yrrGamePlayStateUpdate(YrrGame* g) ;

void yrrFreeGame(YrrGame* game) {
    yrrFreeMedia(game->media);
    yrrFreeBoard(game->board);
    free(game);
}

YrrGame* yrrNewGame(YrrPoint win_sz, YrrPoint board_sz) {

    YrrMedia* media = yrrNewMedia(win_sz);
    if (!media) {
        return NULL;
    }

    YrrBoard* board = yrrNewBoard(board_sz);
    if (!board) {
        return NULL;
    }

    YrrTitle* title = yrrGetTitle();

    YrrGame* rv = malloc(sizeof(YrrGame));
    if (!rv) {
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

    return rv;
}

int yrrResetGame(YrrGame* game) {
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

void yrrChangeStateMethods(YrrGame* game, YrrGameState new_state) {

    switch (new_state) {
        case YrrStatePlay:
            game->process_input = &yrrGamePlayStateProcessInput;
            game->update = &yrrGamePlayStateUpdate;
            game->render = &yrrGamePlayStateRender;
            break;
        default:
            return;
            // todo...
    }
    game->state = new_state;
}

void yrrGamePrintResults(YrrGame* g) {
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

