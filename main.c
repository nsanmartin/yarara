#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <yrr-media.h>
#include <yrr-game.h>
#include <yrr-yarara.h>
#include <yrr-title.h>


enum { NS_PER_SECOND = 1000000000, MS_PER_SECOND = 1000, NS_PER_MS = 1000000 };

long get_time_millis() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec * MS_PER_SECOND + t.tv_nsec / NS_PER_MS;
}


void loop(YrrGame* game) {

    yrr_media_init(game->media);

    long t_last_update_ms = get_time_millis();
    long t_accumulator_ms = 0;
    long t_slice_ms = 300;

    while (!game->quit) {
        long t_delta_ms = get_time_millis() - t_last_update_ms;
        t_last_update_ms += t_delta_ms;
        t_accumulator_ms += t_delta_ms;
        
        for (;!game->quit && t_accumulator_ms > t_slice_ms; t_accumulator_ms -= t_slice_ms) {
            yrr_process_input(game);
            //yrr_update(game);
            game->update(game);
        }
        yrr_game_render(game);
    }

    yrr_media_close(game->media);
    free(game->board->yarara.points);
}

int main () {
    YrrMedia media = {
        .window = NULL,
        .windowWidth = 1790,
        .windowHeight = 924, 
        .renderer = NULL
    };

    YrrBoard board = {
        .width = 124,
        .height = 64,
        .yarara = yrrNewYarara(2400) 
    };

    yrrYararaPushBack(&board.yarara, 3, 0);

    YrrTitle* title = yrrGetTitle();


    YrrGame game = {
        .quit = false,
        .media = &media,
        .state = YrrTitleState,
        .board = &board,
        .update = &yrrGameTitleStateUpdate,
        .title = title
    };

    loop(&game);
}

