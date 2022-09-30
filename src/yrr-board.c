#include <yrr-board.h>
#include <yrr-util.h>

void yrrFreeBoard(YrrBoard* board) {
    yrrFreeYarara(board->yarara);
    free(board);
}

YrrBoard* yrrNewBoard(YrrPoint sz) {

    YrrPoint half = (YrrPoint) { .x = sz.x/2, .y = sz.y/2 };
    YrrPoint first = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    YrrYarara* yarara = yrrNewYarara(1, first);
    if (!yarara) {
        return NULL;
    }

    YrrBoard* rv = malloc(sizeof(YrrBoard));
    if(!rv) {
        return NULL;
    }
    
    *rv = (YrrBoard) {
        .width = sz.x,
        .height = sz.y,
        .yarara = yarara,
        .level = { .food = get_pseudo_rand(half, sz)}
    };

    return rv;
}

void yrrResetBoard(YrrBoard* board) {
    YrrPoint half = (YrrPoint) { .x = board->width/2, .y = board->height/2 };
    YrrPoint first = get_pseudo_rand((YrrPoint) { .x=0, .y=0 }, half);
    yrrResetYarara(board->yarara, first);
}
