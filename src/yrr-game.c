#include <yrr-game.h>
#include <yrr-media.h>
#include <yrr-board.h>

void yrrGamePlayStateProcessInput(YrrGame* game) ;

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

void yrrResetGame(YrrGame* game) {
    yrrResetBoard(game->board);
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
