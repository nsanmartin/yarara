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
    long t_slice_ms = 100;

    while (!game->quit) {
        long t_delta_ms = get_time_millis() - t_last_update_ms;
        t_last_update_ms += t_delta_ms;
        t_accumulator_ms += t_delta_ms;
        
        for (;!game->quit && t_accumulator_ms > t_slice_ms; t_accumulator_ms -= t_slice_ms) {
            game->process_input(game);
            game->update(game);
        }
        game->render(game);
    }

    yrr_media_close(game->media);
    yrr_game_free(game);
}

int main () {
    YrrMedia media = {
        .window = NULL,
        .windowWidth = 1790,
        .windowHeight = 924, 
        .keyQueue = yrrNewKeyQueue(300),
        .renderer = NULL
    };

    if (media.keyQueue.data == NULL) {
        fprintf(stderr, "Memory error\n");
        exit(1);
    }

    YrrBoard board = {
        .width = 124/2,
        .height = 64/2,
        .yarara = yrrNewYarara(2400),
        .level = { .food = { .x = 6, .y = 3 } }
        //.level = { .food = { .x = 124/2, .y = 64/2 } }

    };

    if (board.yarara.points == NULL) {
        fprintf(stderr, "Memory error\n");
        exit(1);
    }
    yrrYararaPushBack(&board.yarara, 0, 0);
    yrrYararaPushBack(&board.yarara, 0, 1);

    YrrTitle* title = yrrGetTitle();


    YrrGame game = {
        .quit = false,
        .media = &media,
        .state = YrrTitleState,
        .board = &board,
        .process_input = &yrrGameTitleStateProcessInput,
        .update = &yrrGameTitleStateUpdate,
        .render = &yrrGameTitleStateRender,
        .title = title
    };

    loop(&game);
}

