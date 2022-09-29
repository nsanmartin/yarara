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
        .windowWidth = 1700,
        .windowHeight = 800, 
        .keyQueue = yrrNewKeyQueue(300),
        .renderer = NULL
    };

    if (media.keyQueue.data == NULL) {
        fprintf(stderr, "Memory error\n");
        exit(1);
    }


    int boardW = 124/2;
    int boardH = 64/2;

    YrrPoint limits = (YrrPoint) { .x = boardW, .y = boardH };
    YrrPoint half = (YrrPoint) { .x = limits.x/2, .y = limits.y/2 };
    YrrPoint first = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    YrrBoard board = {
        .width = boardW,
        .height = boardH,
        .yarara = yrrNewYarara(1, first),
        .level = { .food = get_pseudo_rand(half, limits)}

    };

    printf("limits: (%d, %d)\n", board.width, board.height);
    printf("first: (%d, %d), food0: (%d, %d)\n",
            first.x, first.y, board.level.food.x, board.level.food.y);

    if (board.yarara.data == NULL) {
        fprintf(stderr, "Memory error\n");
        exit(1);
    }
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

