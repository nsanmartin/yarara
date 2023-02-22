#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <yarara.h>

#define SLICE 140

void loop(YrrGame* game) {
    long previous = get_time_millis();
    long lag = 0;
    const long slice = SLICE;

    while (!game->quit) {
        long current = get_time_millis();
        lag += current - previous;
        previous = current;
        
        game->process_input(game);

        for (;!game->quit && lag >= slice; lag -= slice){
            game->update(game);
        }

        game->render(game);
    }
}

void run_game (YrrGame* game) {
    do {
        loop(game);
        yrrGamePrintResults(game);
        if (game->state != YrrStateGameOver) { return; }
        int error = yrrResetGame(game);
        if (error) { return; }
    } while (true);
}

int main(void) {
    YrrPoint win_sz = (YrrPoint) { .x = 1200, .y = 700 };
    YrrPoint board_sz = (YrrPoint) { .x = 69, .y = 40 };
    YrrGame* game = yrrNewGame(win_sz, board_sz);
    if (game == NULL) {
        fprintf(stderr, "Could not load game, exiting.\n");
        return -1;
    } else {
        run_game(game);
    }
    yrrFreeGame(game);
}
