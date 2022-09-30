#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <yrr-media.h>
#include <yrr-game.h>
#include <yrr-yarara.h>
#include <yrr-title.h>
#include <yrr-util.h>
#include <yrr-point.h>

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
    loop(game);
    if (game->state == YrrStateGameOver) {
        YrrPlayer* compu = game->board->players->beg;
        YrrPlayer* human = game->board->players->beg + 1;
        char* winner = compu->yarara->alive ? "compu" : "human";
        printf("Game over, %s won. Human score: %d, compu score: %d.\n",
               winner, human->score, compu->score);
        yrrResetGame(game);
        yrrChangeStateMethods(game, YrrStatePlay);
        run_game(game);
    }
}

int main() {
    YrrPoint win_sz = (YrrPoint) { .x = 1700, .y = 800 };
    YrrPoint board_sz = (YrrPoint) { .x = 124/2, .y = 64/2 };
    YrrGame* game = yrrNewGame(win_sz, board_sz);
    run_game(game);
}
