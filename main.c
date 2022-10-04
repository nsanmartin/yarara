#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <yarara.h>

#define SLICE 180

void loop(YrrGame* game) {
    long previous = get_time_millis();
    long lag = 0;
    const long slice = SLICE;

    while (!game->quit) {
        long current = get_time_millis();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;
        
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

int main() {
    YrrPoint win_sz = (YrrPoint) { .x = 1700, .y = 800 };
    YrrPoint board_sz = (YrrPoint) { .x = 124/2, .y = 64/2 };
    YrrGame* game = yrrNewGame(win_sz, board_sz);
    if (game == NULL) {
        fprintf(stderr, "Could not load game, exiting.\n");
    }
    run_game(game);
}
