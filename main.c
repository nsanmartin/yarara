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

    long previous = get_time_millis();
    long lag = 0;
    const long slice = 100;

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
        .yarara = yrrNewYarara(1),
        .level = { .food = { .x = 6, .y = 3 } }

    };

    if (board.yarara.data == NULL) {
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
        .title = title,
        .points = 0
    };

    loop(&game);

    if(game.state == YrrGameOverState) {
        printf("Game over, you ate %d apples!\n", game.points);
    } else {
        printf("Player quited, after eating %d apples!\n", game.points);
    }
}

